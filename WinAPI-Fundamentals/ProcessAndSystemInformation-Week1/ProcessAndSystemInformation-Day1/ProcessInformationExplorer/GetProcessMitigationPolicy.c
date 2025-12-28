#include <windows.h>
#include <stdio.h>
#include <processthreadsapi.h>  // Needed for GetProcessMitigationPolicy

typedef BOOL (WINAPI *pGetProcessMitigationPolicy)(
    HANDLE hProcess,
    PROCESS_MITIGATION_POLICY MitigationPolicy,
    PVOID lpBuffer,
    SIZE_T dwLength
);

int main(void)
{
    PROCESS_MITIGATION_DEP_POLICY dep = {0};
    PROCESS_MITIGATION_ASLR_POLICY aslr = {0};
    PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY cfg = {0};

    HANDLE hProcess = GetCurrentProcess();
    pGetProcessMitigationPolicy GetProcessMitigationPolicy = (pGetProcessMitigationPolicy)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetProcessMitigationPolicy");
    // DEP
    if (GetProcessMitigationPolicy(hProcess, ProcessDEPPolicy, &dep, sizeof(dep))) {
        printf("DEP Enabled: %s\n", dep.Enable ? "Yes" : "No");
        printf("DEP Permanent: %s\n", dep.Permanent ? "Yes" : "No");
    }

    // ASLR
    if (GetProcessMitigationPolicy(hProcess, ProcessASLRPolicy, &aslr, sizeof(aslr))) {
        printf("ASLR Enabled: %s\n", aslr.EnableForceRelocateImages ? "Yes" : "No");
    }

    // Control Flow Guard (CFG)
    if (GetProcessMitigationPolicy(hProcess, ProcessControlFlowGuardPolicy, &cfg, sizeof(cfg))) {
        printf("CFG Enabled: %s\n", cfg.EnableControlFlowGuard ? "Yes" : "No");
    }

    return 0;
}
