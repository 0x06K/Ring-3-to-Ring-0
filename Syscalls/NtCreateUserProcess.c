NTSTATUS NtCreateUserProcess(
    PHANDLE ProcessHandle,          // [rbp+90h]
    PHANDLE ThreadHandle,           // [rbp+88h]
    ACCESS_MASK ProcessDesiredAccess, // r8d -> [rbp+2Ch]
    ACCESS_MASK ThreadDesiredAccess,  // r9d -> [rbp+28h]
    POBJECT_ATTRIBUTES ProcessObjAttr, // [rbp+770h] -> r14
    POBJECT_ATTRIBUTES ThreadObjAttr,  // [rbp+778h]
    ULONG ProcessFlags,             // [rbp+780h] -> r12d
    ULONG ThreadFlags,              // [rbp+788h]
    PRTL_USER_PROCESS_PARAMETERS ProcessParams, // [rbp+790h]
    PPROCESS_CREATE_INFO CreateInfo,  // rsi <- [rbp+798h]
    PPROCESS_ATTRIBUTE_LIST AttrList  // rbx <- [rbp+7A0h]
)
{
    NTSTATUS status;
    HANDLE hProcess = NULL, hThread = NULL;
    HANDLE hSection = NULL, hFile = NULL;
    PVOID pSection = NULL, pFileObject = NULL;
    PEPROCESS ParentProcess = NULL, NewProcess = NULL;
    PETHREAD NewThread = NULL;
    PTOKEN Token = NULL;
    PVOID ServerSilo = NULL;
    PS_CREATE_INFO localCreateInfo = {0};
    PS_ATTRIBUTE_LIST localAttrList = {0};
    OBJECT_ATTRIBUTES objAttr;
    IO_STATUS_BLOCK iosb;
    BOOLEAN isKernelMode;
    ULONG contextLength;
    PCONTEXT extContext = NULL;

    // --- Prologue / stack setup (788h bytes of locals, security cookie) ---

    // Zero out local buffers
    memset(&localCreateInfo, 0, 0x190);  // [rbp+3B0h], size r15d=190h
    memset(localAttrList_buffer, 0, 0x190); // [rbp+540h]

    // Capture current thread/process info
    PKTHREAD CurrentThread = KeGetCurrentThread(); // gs:[188h]
    ParentProcess = PsGetCurrentProcess();          // [CurrentThread+B8h] -> r13
    isKernelMode = CurrentThread->PreviousMode;     // [CurrentThread+232h] -> r15b

    // --- Validate flags ---
    if (ProcessFlags & 0xFFFB6838) return STATUS_INVALID_PARAMETER;
    if (ThreadFlags & 0xFFFFFFFE) return STATUS_INVALID_PARAMETER;

    // Bits 0xC00 (PROCESS_CREATE_FLAGS_BREAKAWAY | PROTECTED) can't both be set
    if ((ProcessFlags & 0x8400) == 0x8400)
        return STATUS_INVALID_PARAMETER; // 0xC0000030

    // --- Probe user pointers if previous mode is user ---
    if (isKernelMode) {
        // Probe ProcessHandle and ThreadHandle pointers
        ProbeForWrite(ProcessHandle, sizeof(HANDLE), ...);
        ProbeForWrite(ThreadHandle, sizeof(HANDLE), ...);
    }

    // --- Validate ProcessObjAttr alignment ---
    if (ProcessObjAttr) {
        if (isKernelMode) {
            if ((ULONG_PTR)ProcessObjAttr & 3) ExRaiseDatatypeMisalignment();
            ProbeForRead(ProcessObjAttr, 1, 1);
        }
        // Capture create flags from ProcessObjAttr
        ULONG createFlags = ProcessObjAttr->Attributes;
        if (isKernelMode)
            createFlags &= 0x11FF2;
        else
            createFlags &= 0x1DF2;
        captured_create_flags = createFlags; // [rbp+530h]
    }

    // --- Build process context from attribute list ---
    memset(&localAttrList, 0, 0x208);
    if (AttrList) {
        status = PspBuildCreateProcessContext(AttrList, isKernelMode, 0, &localAttrList);
        if (!NT_SUCCESS(status)) goto cleanup;
    }

    // --- Handle PROCESS_CREATE_FLAGS_INHERIT_HANDLES + image subsystem check ---
    if ((ProcessFlags & 0x40) && (localAttrList.Flags & 0x20000)) {
        if (localCreateInfo.ImageSubsystem == 0) {
            ProcessFlags &= ~0x40;
            localAttrList.Flags &= ~(1 << 17);
        }
    }

    // --- Check for WSL / pico process flags ---
    if (!(ProcessFlags & 0x4)) {
        if (localAttrList.Flags & 0x800)
            goto error_invalid; // STATUS_INVALID_PARAMETER_MIX
    }

    // --- Capture create info from user ---
    status = PspCaptureCreateInfo(&localAttrList, CreateInfo, isKernelMode);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Reference parent process handle if provided ---
    if (localAttrList.Flags & 1) {
        status = ObpReferenceObjectByHandleWithTag(
            localAttrList.ParentProcess,
            0x80,  // PROCESS_CREATE_PROCESS
            PsProcessType,
            isKernelMode,
            &ParentProcess,
            NULL,
            'PsCr');
        if (!NT_SUCCESS(status)) goto cleanup_createinfo;
        localAttrList.ParentProcessObject = ParentProcess;
    } else {
        // Use current process as parent
        localAttrList.ParentProcessObject = ParentProcess;
    }

    // --- Estimate server silo for new process ---
    ServerSilo = PspEstimateNewProcessServerSilo(
        ParentProcess,
        localAttrList.JobObject,
        localAttrList.JobObjectFlags);

    // --- Check for same-silo process creation restrictions ---
    UCHAR siloFlags = (localAttrList.Flags >> 2) & 0xC;
    if (siloFlags == 4) {
        if (ParentProcess != CurrentProcess) goto error_invalid;
        if (CurrentProcess->Flags & (1 << 12)) goto error_invalid;
    }

    // --- Reference token for new process ---
    status = PspReferenceTokenForNewProcess(
        ParentProcess,
        localAttrList.Token,
        isKernelMode,
        &Token);
    if (!NT_SUCCESS(status)) {
        localAttrList.Token = NULL;
        goto cleanup_createinfo;
    }

    // --- If explicit token provided, check silo containment ---
    if (localAttrList.Token) {
        PVOID TokenSilo;
        status = SeQueryServerSiloToken(Token, &TokenSilo);
        if (NT_SUCCESS(status)) {
            if (!PspIsSiloInSilo(TokenSilo, ServerSilo))
                goto error_invalid;
        }
    }

    // --- Handle PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL ---
    if (localAttrList.Flags & 0x20) {
        // Check if this is an inheritance scenario
        BOOLEAN inheritProtection = (localAttrList.Flags & 0x20000)
            ? (BOOLEAN)(localCreateInfo.InheritFromParent & 1)
            : FALSE;
        protection_byte = inheritProtection;

        // Debug: if NtGlobalFlag has 0x40000 set, capture image name for debug
        if (NtGlobalFlag & 0x40000) {
            RtlCopyMemory(&debugBuffer, &localAttrList.ImageName, 0x10);
            ZwSystemDebugControl(0x26, &debugBuffer, 0x10, NULL, 0, NULL);
        }

        // Query signing policy
        ULONG signingPolicy = (ProcessFlags >> 6) & 1;
        status = SeQuerySigningPolicy(
            Token,
            &localAttrList.ImageInfo,
            inheritProtection,
            &protection_out,
            &mitigation_out,
            &signing_out);
        if (!NT_SUCCESS(status)) goto cleanup_createinfo;
    }

    // --- Set up OB_OPEN_REASON and object attributes for image file ---
    OA.Length = 0x30;
    OA.RootDirectory = NULL;
    OA.ObjectName = &localAttrList.ImageName;
    OA.Attributes = (isKernelMode == 1) ? 0x240 : 0x640;
    OA.SecurityDescriptor = NULL;
    OA.SecurityQualityOfService = NULL;

    // Call kernel callback if registered (g_kernelCallbacks[0xB0])
    if (g_kernelCallbacks_ImageCallback) {
        status = g_kernelCallbacks_ImageCallback(Token);
        if (!NT_SUCCESS(status)) goto cleanup_createinfo;
    }

    // --- Get memory partition ---
    status = PspGetMemoryPartitionContext(
        ParentProcess, ProcessFlags,
        localAttrList.JobObject, localAttrList.JobObjectFlags,
        &PartitionHandle);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Create ECP list for the image file open ---
    status = PspCreateUserProcessEcp(Token, &ecpList);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Open the image file (IoCreateFileEx) ---
    ULONG fileFlags = localAttrList.FileFlags | 0x100020;
    status = IoCreateFileEx(
        &hFile,
        fileFlags,
        &OA,
        &iosb,
        NULL, 0,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        FILE_OPEN,
        FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
        NULL, 0,
        CreateFileTypeNone,
        &ecpList,
        IO_NO_PARAMETER_CHECKING);

    if (!NT_SUCCESS(status)) {
        // Retry without extra flags if explicit dir was specified
        if (localAttrList.FileFlags != 0) {
            status = IoCreateFileEx(
                &hFile, 0x100020, &OA, &iosb,
                NULL, 0, FILE_SHARE_READ | FILE_SHARE_DELETE,
                FILE_OPEN, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
                NULL, 0, CreateFileTypeNone, &ecpList, IO_NO_PARAMETER_CHECKING);
        }
    }

    if (!NT_SUCCESS(status)) {
        hFile = NULL;
        PspUpdateCreateInfo(&localAttrList, 1, NULL);
        goto cleanup_createinfo;
    }

    // --- Reference file object ---
    status = ObReferenceObjectByHandle(
        hFile, 0x100020, IoFileObjectType,
        KernelMode, &pFileObject, NULL);
    if (!NT_SUCCESS(status)) {
        pFileObject = NULL;
        goto cleanup_handles;
    }

    // --- Determine if debug port needed ---
    BOOLEAN hasDebugPort = (localAttrList.DebugPort != NULL);
    createSubMode = hasDebugPort ? 5 : 1;

    // --- Duplicate token with origin claim if needed ---
    if (localAttrList.OriginToken) {
        status = SeDuplicateTokenAndAddOriginClaim(
            Token, localAttrList.OriginToken, localAttrList.OriginTokenFlags,
            &newToken);
        if (NT_SUCCESS(status))
            useNewToken = TRUE;
    }

    // --- Create image section ---
    status = MmCreateSpecialImageSection(
        &hSection,
        &OA_section,
        Token_for_section,
        signingPolicy,
        hFile);
    if (!NT_SUCCESS(status)) goto cleanup_section;

    // --- Reference section object ---
    status = ObReferenceObjectByHandle(hSection, 8, MmSectionObjectType, KernelMode, &pSection, NULL);
    if (!NT_SUCCESS(status)) { pSection = NULL; goto cleanup_section; }

    // --- Get process protection requirements from image ---
    status = PspGetProcessProtectionRequirementsFromImage(pSection, protection_byte, &protection_out);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Check if protection level changed, re-query signing policy ---
    if (required_protection != current_protection) {
        status = SeQuerySigningPolicy(Token, &localAttrList.ImageInfo,
            signingPolicy, &new_protection, &new_mitigation, &new_signing);
        if (!NT_SUCCESS(status)) goto cleanup_createinfo;

        // Check signing level compatibility
        UCHAR sigLevel = new_signing & 0x30;
        UCHAR reqLevel = current_signing & 0x30;
        if (sigLevel && (new_signing & 0x30) != reqLevel)
            goto error_invalid;

        // Invoke CI callback if registered (SeCiCallbacks+0x40)
        if (!SeCiCallbacks_VerifyProtection)
            goto error_invalid;
        if (!SeCiCallbacks_VerifyProtection(new_signing, current_signing))
            goto error_invalid;

        // Close old section, reopen with new params
        ObCloseHandle(hSection, KernelMode);
        ObDereferenceObject(pSection);
        hSection = NULL; pSection = NULL;

        // Re-create image section with updated signing
        // ... (jumps back to MmCreateSpecialImageSection path)
    }

    // --- Validate process protection ---
    status = PspValidateCreateProcessProtection(
        ParentProcess, &localAttrList, isKernelMode, ProcessFlags,
        protection_byte);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Check for invalid access by protection level ---
    if (!(ProcessFlags & (1 << 18))) {
        UCHAR parentProtection = ParentProcess->Protection.Level;
        UCHAR newProtection = protection_byte & 7;
        if (newProtection != 0) {
            if (PspCheckForInvalidAccessByProtection(protection_byte, parentProtection, isKernelMode))
                localAttrList.Flags |= 8; // PS_CREATE_INFO_FLAG_PROTECTED_PROCESS_INVALID
        }
    }

    // --- Capture process parameters ---
    PspGetProcessParameterOverrides(localAttrList.DebugPort, &overrides);
    status = PspCaptureProcessParameters(&localAttrList, ProcessParams, isKernelMode);
    if (!NT_SUCCESS(status)) {
        localAttrList.Flags &= ~4;
        goto cleanup_createinfo;
    }

    // --- Allocate process object ---
    status = PspAllocateProcess(
        ParentProcess,
        isKernelMode,
        Token,
        pSection,            // image section
        localAttrList.JobObject,
        localAttrList.JobObjectFlags,
        ProcessFlags,
        Token,               // effective token
        &localAttrList,
        hasDebugPort,
        localAttrList.DebugPort,
        &NewProcess,
        &ProcessHandle_out,
        &ThreadHandle_out);
    if (!NT_SUCCESS(status)) goto cleanup_createinfo;

    // --- Determine XSTATE context length ---
    ULONG xstateFeatures = 0x10001B;
    if (NewProcess->Flags & 0x4000) {
        xstateFeatures |= 0x100040;
    }
    RtlGetExtendedContextLength2(xstateFeatures, &contextLength, xstateMask);

    // Allocate aligned stack space for XSTATE context
    contextLength = ALIGN_UP(contextLength, 16);
    extContext = alloca(contextLength);
    memset(extContext, 0, contextLength);
    RtlInitializeExtendedContext2(extContext, xstateFeatures, &contextController, xstateMask);

    // --- Set up initial thread context ---
    if (pSection) {
        // Has image section: create user context from image entry point
        PVOID userThreadStart = PspUserThreadStart;
        status = PspCreateUserContext(
            extContext,
            1,              // user mode
            userThreadStart,
            localAttrList.InitialTeb);
    } else {
        // No section: clone context from current thread
        status = PspGetContextThreadInternal(
            CurrentThread, extContext, 0, 1, KernelMode);
        if (!NT_SUCCESS(status)) {
            // Release process rundown protection
            LONGLONG prev = InterlockedAdd64(&NewProcess->RundownProtect, -1);
            if ((prev & 6) == 2)
                ExfTryToWakePushLock(&NewProcess->RundownProtect);
            KeAbPostRelease(&NewProcess->RundownProtect);
            KeLeaveCriticalRegionThread(CurrentThread);
            PspRundownSingleProcess(NewProcess, 0);
            goto cleanup_createinfo;
        }
        extContext->Dr7 = 0x129; // set debug status
    }

    // --- Reference process with tag for cleanup ---
    ObfReferenceObjectWithTag(NewProcess, 'PsCr');

    // --- Write client IDs back if output buffer provided ---
    if (ProcessHandle_out) {
        ProcessHandle_out->UniqueProcess = NewProcess->UniqueProcessId;
        ULONG stackSize = max(localAttrList.StackReserve, 0x40000);
        ProcessHandle_out->StackReserve = stackSize;
        ProcessHandle_out->StackCommit = localAttrList.StackCommit;
        ProcessHandle_out->UniqueThread = localAttrList.InitialTid;
    }

    // --- Map thread creation flags ---
    ULONG threadCreateFlags = 0;
    PspMapThreadCreationFlags(ThreadFlags, &threadCreateFlags);

    if (localAttrList.SuspendedProcess)
        createSubMode = 2, threadCreateFlags |= THREAD_CREATE_FLAGS_CREATE_SUSPENDED;

    if (localAttrList.SuspendedThread)
        ProcessFlags |= (1 << 10);

    // --- Set up thread attribute list ---
    threadAttrList.TotalLength = sizeof(threadAttrList);
    localAttrList.ThreadAttributeList = &threadAttrList;
    threadCreateFlags |= 0x60; // internal flags

    // --- Allocate thread object ---
    status = PspAllocateThread(
        NewProcess, isKernelMode,
        &localAttrList,
        ThreadAttrList,
        &threadAttrList,
        threadCreateFlags,
        NULL, NULL,
        &extContext,
        createSubMode,
        &NewThread,
        &ThreadHandle_out);
    if (!NT_SUCCESS(status)) {
        // Release process rundown, cleanup
        InterlockedAdd64(&NewProcess->RundownProtect, -1);
        // ... wake pushlock, leave critical region
        PspRundownSingleProcess(NewProcess, 0);
        goto cleanup_handles;
    }

    // --- Test protected process incompatibility ---
    PsTestProtectedProcessIncompatibility(NewProcess, ParentProcess, isKernelMode);

    // Apply access mask restrictions for protected processes via RtlProtectedAccess table
    if (incompatible) {
        if (ProcessDesiredAccess & 0x2000000) {
            // Mask out disallowed access bits from table
            ULONG mask = RtlProtectedAccess[protectionLevel * 3 + 1];
            ProcessDesiredAccess |= (~mask & 0x1FFFFF);
            ProcessDesiredAccess &= ~(1 << 25);
            if (localAttrList.ParentProcessObject == ParentProcess)
                ProcessDesiredAccess |= 1;
        }
        if (ThreadDesiredAccess & 0x2000000) {
            ULONG mask = RtlProtectedAccess[protectionLevel * 3 + 2];
            ThreadDesiredAccess |= (~mask & 0x1FFFFF);
            ThreadDesiredAccess &= ~(1 << 25);
            if (localAttrList.ParentProcessObject == ParentProcess)
                ThreadDesiredAccess |= 1;
        }
    }

    // --- Insert process into process list / job ---
    PACCESS_STATE accessState;
    if (localAttrList.SecurityDescriptor)
        accessState = localAttrList.SecurityDescriptor + 0x70;
    else
        accessState = NULL;

    status = PspInsertProcess(
        NewProcess,
        ParentProcess,
        ProcessFlags,
        localAttrList.JobObject,
        createSubMode,
        accessState,
        &localAttrList.ProcessAccessState);
    NTSTATUS insertStatus = status;

    // --- Insert thread ---
    status = PspInsertThread(
        NewThread,              // thread object
        NewProcess,             // process
        &localAttrList.ThreadAttributeList,
        &threadCreateFlags,
        NULL, NULL,
        r12_clientIdOut,
        &localAttrList.ThreadClientId,
        &localAttrList);
    KeLeaveCriticalRegionThread(CurrentThread);

    if (!NT_SUCCESS(insertStatus)) {
        PspRundownSingleProcess(NewProcess, 0);
        status = insertStatus;
        goto cleanup_handles;
    }

    if (!NT_SUCCESS(status)) goto error_terminate;

    // --- Verify silo assignment matches estimate ---
    if (PsGetProcessServerSilo(NewProcess) != ServerSilo) {
        status = 0xC000022D; // STATUS_PROCESS_IS_PROTECTED
        goto error_terminate;
    }

    // --- Create object handle for process ---
    status = PspCreateObjectHandle(
        NewProcess, ProcessDesiredAccess,
        &localAttrList.ProcessAccessState, &ProcessHandle_out);
    if (!NT_SUCCESS(status)) goto cleanup_process_handle;

    // --- Copy client info back to caller output buffer ---
    if (localAttrList.ClientInfo) {
        RtlCopyMemory(localAttrList.ClientInfo, &localAttrList.ProcessId, 0x40);
    }

    // Write process handle to caller
    *ProcessHandle = localAttrList.ProcessHandleOut;

    // --- Call PspUpdateCreateInfo with final state ---
    status = PspUpdateCreateInfo(NewProcess, &localAttrList, 6);
    if (!NT_SUCCESS(status)) goto cleanup_process_handle;

    status = STATUS_SUCCESS;
    goto cleanup_finish;

cleanup_process_handle:
    // Close process handle if open
    BOOLEAN closeKernel = !(localAttrList.Flags & 0x200)
        && (NewProcess->Flags & 0x1000);
    ObCloseHandle(hProcessHandle, closeKernel ? KernelMode : UserMode);

cleanup_thread_handle:
    BOOLEAN closeThreadKernel = !(localAttrList.ThreadFlags & 0x200)
        && (NewProcess->Flags & 0x1000);
    ObCloseHandle(hThreadHandle, closeThreadKernel ? KernelMode : UserMode);

cleanup_finish:
    SepDeleteAccessState(&localAttrList.ProcessAccessState);
    SeReleaseSubjectContext(&localAttrList.SubjectContext);

error_terminate:
    if (!NT_SUCCESS(status))
        PsTerminateProcess(NewProcess, status);

cleanup_handles:
    ObDereferenceObject(NewThread);
    ObfDereferenceObjectWithTag(NewProcess, 'PsCr');

error_invalid:
    status = STATUS_INVALID_PARAMETER; // 0xC000000D

cleanup_createinfo:
    // Cleanup file object origin claim
    if (pFileObject)
        SeDeleteCodeIntegrityOriginClaimForFileObject(pFileObject);

    // Dereference job object if captured
    if (localAttrList.JobObject)
        ObfDereferenceObjectWithTag(localAttrList.JobObject, 'PsJb');

    PspDeleteCreateProcessContext(&localAttrList);

    // Free ECP list
    if (ecpList)
        FsRtlFreeExtraCreateParameterList(ecpList);

    // Dereference token
    if (tokenRefed)
        ObDereferenceObject(Token);

    return status;
}
