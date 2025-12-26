/***************************************************************
 *  Process Enumerator
 *  ------------------------------------------------------------
 *  Description:
 *      Enumerates all running processes on the system using
 *      Windows Tool Help APIs. Supports both 32-bit and 64-bit
 *      processes when compiled as a 64-bit application.
 *
 *  Features:
 *      - Lists active processes
 *      - Handles WOW64 (32-bit on 64-bit) processes
 *
 *  APIs Used:
 *      - CreateToolhelp32Snapshot
 *      - Process32First / Process32Next
 *
 *  Platform:
 *      Windows 10  (x64 recommended)
 *
 *  Build Configuration:
 *      x64 | Release / Debug
 *
 *  Author:
 *      0x06k
 *
 *  Notes:
 *      - Some system processes are protected and cannot be opened.
 *      - Administrator privileges may be required for full access.
 *
 ***************************************************************/

#include <windows.h>
#include <tlhelp32.h> // tlhelp32.h relies on windows.h
#include <stdio.h>
#include "colors.h"

void EnableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;

    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
}

void main(){
  EnableANSIColors();
  printf(CLR_BOLD CLR_GREEN "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  printf( "||              P R O C E S S  E N U M E R A T O R              ||\n");
  printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" CLR_RESET);
  /*
    CreateToolhelp32Snapshot Function (tlhelp32.h)

    Description:
        Creates a snapshot of the specified processes, threads, modules,
        and heaps currently present in the system. The snapshot is used by
        other Tool Help functions to enumerate system objects.

    Syntax:
        HANDLE CreateToolhelp32Snapshot(
            [in] DWORD dwFlags,
            [in] DWORD th32ProcessID
        );

    Parameters:
        [in] dwFlags
            Specifies which portions of the system to include in the snapshot.
            This parameter can be one or more of the following values:

            TH32CS_INHERIT (0x80000000)
                Allows the snapshot handle to be inherited by child processes.

            TH32CS_SNAPALL
                Includes all processes, threads, heaps, and modules.
                Equivalent to:
                TH32CS_SNAPHEAPLIST | TH32CS_SNAPMODULE |
                TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD

            TH32CS_SNAPHEAPLIST (0x00000001)
                Includes all heaps of the specified process.
                Enumerated using Heap32ListFirst / Heap32ListNext.

            TH32CS_SNAPMODULE (0x00000008)
                Includes all modules of the specified process.
                - On 32-bit systems: includes 32-bit modules.
                - On 64-bit systems: includes 64-bit modules.
                To enumerate 32-bit modules from a 64-bit process,
                use TH32CS_SNAPMODULE32.

            TH32CS_SNAPMODULE32 (0x00000010)
                Includes 32-bit modules of the specified process when
                called from a 64-bit application.

            TH32CS_SNAPPROCESS (0x00000002)
                Includes all processes in the system.
                Enumerated using Process32First / Process32Next.

            TH32CS_SNAPTHREAD (0x00000004)
                Includes all threads in the system.
                Enumerated using Thread32First / Thread32Next.
                Threads belonging to a process can be identified using
                the th32OwnerProcessID field of THREADENTRY32.

        [in] th32ProcessID
            The process ID to target for heap or module enumeration.
            - Use 0 to specify the current process.
            - Required when using TH32CS_SNAPHEAPLIST,
              TH32CS_SNAPMODULE, or TH32CS_SNAPMODULE32.
            - Ignored when enumerating all processes.

            Special cases:
            - Accessing the Idle or CSRSS processes fails with ERROR_ACCESS_DENIED.
            - Calling from a 32-bit process against a 64-bit target may fail
              with ERROR_PARTIAL_COPY (299).

    Return Value:
        On success:
            Returns a valid HANDLE to the snapshot.

        On failure:
            Returns INVALID_HANDLE_VALUE.
            Call GetLastError() for extended error information.

    Remarks:
        - The snapshot is read-only and represents a moment-in-time view
          of the system.
        - The snapshot handle must be released using CloseHandle().
        - When enumerating heaps or modules for other processes, the function
          may fail or return partial data if:
              • The target process is starting or terminating
              • The module list changes during enumeration
              • The process loader data is unavailable
        - If ERROR_BAD_LENGTH occurs when using TH32CS_SNAPMODULE or
          TH32CS_SNAPMODULE32, retry the call until it succeeds.
        - Modules loaded using LOAD_LIBRARY_AS_DATAFILE are not included.
        - To retrieve full executable paths for both 32-bit and 64-bit
          processes from a 32-bit application, use QueryFullProcessImageName().

    Notes:
        - Always close the snapshot handle with CloseHandle().
        - 64-bit applications can enumerate both 32-bit and 64-bit processes.
        - 32-bit applications cannot enumerate 64-bit process modules.
*/
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  /*
    GetLastError Function (errhandlingapi.h)

    Description:
        Retrieves the calling thread's last-error code. The last-error value
        is maintained on a per-thread basis, meaning each thread has its own
        independent error state.

        This function should be called immediately after a function reports
        a failure, as subsequent API calls may overwrite the last-error code.

    Syntax:
        DWORD GetLastError(void);

    Return Value:
        Returns the calling thread’s last-error code.

        Note:
            - The returned value is meaningful only if the previous function
              explicitly documents that it sets the last-error code.
            - Some functions set the last-error code even on success.
            - Other functions do not modify the last-error code at all.

    Remarks:
        - The last-error code is set by Windows API functions via SetLastError.
        - Always call GetLastError immediately after a function failure;
          otherwise, the value may be overwritten by subsequent API calls.
        - The returned error code is thread-specific and does not affect
          other threads in the same process.

        - To obtain a human-readable description of the error code, use
          the FormatMessage function.

        - Error codes are 32-bit values:
            * Bit 31 is the sign bit.
            * Bit 29 is reserved for application-defined error codes.
              (System-defined error codes never set this bit.)

        - Application-defined error codes should set bit 29 to ensure
          they do not conflict with system-defined error values.

        - To convert a system error code to an HRESULT, use:
              HRESULT_FROM_WIN32(errorCode)

    Usage Notes:
        - Do not cache or reuse the error code beyond the scope of the failure.
        - Calling another Win32 API before GetLastError may overwrite the value.
        - Some APIs reset the error code to zero on success.

    Example:
        if (!SomeWinApiFunction()) {
            DWORD err = GetLastError();
            // Handle error
        }

    Requirements:
        Minimum supported client: Windows XP (desktop apps)
        Minimum supported server: Windows Server 2003
        Header:  errhandlingapi.h (include <Windows.h>)
        Library: Kernel32.lib
        DLL:     Kernel32.dll
*/

  if(hSnapshot == INVALID_HANDLE_VALUE){
    DWORD err = GetLastError();
    printf("ERROR CODE: %ul\n", err);
    return;
  }


/*
    Process32First Function (tlhelp32.h)

    Description:
        Retrieves information about the first process in a system snapshot
        created by the CreateToolhelp32Snapshot function. This function
        initializes the enumeration of processes within the snapshot.

    Syntax:
        BOOL Process32First(
            [in]      HANDLE           hSnapshot,
            [in, out] LPPROCESSENTRY32 lppe
        );

    Parameters:
        [in] hSnapshot
            A handle to a snapshot previously created by
            CreateToolhelp32Snapshot.

        [in, out] lppe
            A pointer to a PROCESSENTRY32 structure that receives
            information about the first process in the snapshot.

            Before calling this function, the dwSize member of the
            PROCESSENTRY32 structure must be set to:
                sizeof(PROCESSENTRY32)

    Return Value:
        Returns TRUE if the first process entry was successfully retrieved.

        Returns FALSE if the function fails or if no process entries exist.
        When the function fails, call GetLastError() to retrieve extended
        error information.

        If the snapshot contains no processes, GetLastError() returns
        ERROR_NO_MORE_FILES.

    Remarks:
        - This function must be called before Process32Next to begin
          process enumeration.
        - The snapshot handle must be valid and obtained from
          CreateToolhelp32Snapshot.
        - The PROCESSENTRY32 structure must be properly initialized
          before calling this function.
        - The snapshot remains static; changes to the system after the
          snapshot is taken are not reflected.

    Example Usage:
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnapshot, &pe)) {
            do {
                // Process information available in 'pe'
            } while (Process32Next(hSnapshot, &pe));
        }


*/
  PROCESSENTRY32 pe;
  pe.dwSize = sizeof(PROCESSENTRY32);
  /*
      typedef struct tagPROCESSENTRY32 {
        DWORD     dwSize;
        DWORD     cntUsage;
        DWORD     th32ProcessID;
        ULONG_PTR th32DefaultHeapID;
        DWORD     th32ModuleID;
        DWORD     cntThreads;
        DWORD     th32ParentProcessID;
        LONG      pcPriClassBase;
        DWORD     dwFlags;
        CHAR      szExeFile[MAX_PATH];
      } PROCESSENTRY32;
      /*
    PROCESSENTRY32 Structure (tlhelp32.h)

    Description:
        Contains information about a process in a system snapshot created
        by CreateToolhelp32Snapshot. Used with Process32First and Process32Next
        to enumerate processes.

    Fields:

        DWORD dwSize
            - Size, in bytes, of this structure.
            - Must be set to sizeof(PROCESSENTRY32) before calling
              Process32First or Process32Next.
            - it basically helps when microsoft developers send some updates
              they don't have to update the size again and again.

        DWORD cntUsage
            - The number of references to the process.
            - Usually not useful for typical applications; maintained by the system.

        DWORD th32ProcessID
            - The unique process identifier (PID) of the process.
            - Can be used with OpenProcess to obtain a handle to the process.

        ULONG_PTR th32DefaultHeapID
            - The default heap ID of the process.
            - Internal value used by the system for memory management.

        DWORD th32ModuleID
            - Reserved, typically zero.
            - Historically used to identify the first module associated with the process.

        DWORD cntThreads
            - Number of execution threads currently in the process.
            - Can be used to get an idea of process activity or load.

        DWORD th32ParentProcessID
            - The process identifier (PID) of the parent process.
            - Useful for creating a process tree or understanding relationships.

        LONG pcPriClassBase
            - The base priority class of the process.
            - Can be used to estimate CPU scheduling priority.

        DWORD dwFlags
            - Reserved, usually zero.
            - May contain system-specific flags in future implementations.

        CHAR zExeFile[MAX_PATH]
            - Null-terminated string containing the executable filename.
            - Only the **name** of the executable, not the full path.
*/

  // Start process enumeration
    if (Process32First(hSnapshot, &pe)) {
        do {
          printf(CLR_GREEN "\n[+] Enumerating Process\n" CLR_RESET);
          printf(CLR_CYAN  "------------------------------------------------------------\n" CLR_RESET);

          printf(CLR_YELLOW "%-20s" CLR_WHITE "%s\n",  "Process Name:",      pe.szExeFile);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%lu\n", "Process ID (PID):",  pe.th32ProcessID);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%lu\n", "Parent PID:",        pe.th32ParentProcessID);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%lu\n", "Threads:",           pe.cntThreads);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%ld\n", "Base Priority:",     pe.pcPriClassBase);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%lu\n", "Usage Count:",       pe.cntUsage);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "%lu\n", "Module ID:",         pe.th32ModuleID);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "0x%p\n", "Default Heap:",     (void*)pe.th32DefaultHeapID);
          printf(CLR_YELLOW "%-20s" CLR_WHITE "0x%lx\n", "Flags:",            pe.dwFlags);

          printf(CLR_CYAN  "------------------------------------------------------------\n" CLR_RESET);


        } while (Process32Next(hSnapshot, &pe));  // Continue to the next process
    } else {
        DWORD err = GetLastError();
        printf("Process32First failed. Error: %lu\n", err);
    }
    CloseHandle(hSnapshot);
    // CreateToolhelp32Snapshot() -> Process32First() -> Process32Next();
}







/*
    Difference Between Process32First and Process32Next

    Usage:
        - Process32First:
            • Initializes enumeration of processes in a snapshot.
            • Must be called first before calling Process32Next.
            • Copies the first process entry into a PROCESSENTRY32 structure.

        - Process32Next:
            • Continues enumeration after Process32First.
            • Copies the next process entry into the PROCESSENTRY32 structure.
            • Returns FALSE when there are no more processes.

    Parameters:
        Both functions take the same parameters:

        1. HANDLE hSnapshot
            - Handle to a snapshot created with CreateToolhelp32Snapshot.
            - Must remain valid throughout enumeration.

        2. LPPROCESSENTRY32 lppe
            - Pointer to a PROCESSENTRY32 structure that receives process information.
            - The dwSize member must be set to sizeof(PROCESSENTRY32) before calling either function.

    Coding Notes:
        - Always call Process32First before Process32Next.
        - Loop through processes using a do-while pattern:

            PROCESSENTRY32 pe;
            pe.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(hSnap, &pe)) {
                do {
                    // Access process info in 'pe'
                } while (Process32Next(hSnap, &pe));
            }

        - Both functions return TRUE on success, FALSE on failure.
        - When FALSE is returned and GetLastError() == ERROR_NO_MORE_FILES, the enumeration has completed.

    Summary:
        - Process32First: initializes and retrieves the first process.
        - Process32Next: retrieves subsequent processes until the end of the snapshot.
*/
