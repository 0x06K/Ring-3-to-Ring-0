// don't use this method.
#include <windows.h>
#include <winternl.h>
#include <stdio.h>

#pragma comment(lib, "ntdll.lib")

// Function prototype (undocumented)
typedef NTSTATUS (NTAPI *LdrEnumerateLoadedModules_t)(
    ULONG Flags,
    PVOID Callback,
    PVOID Context
);



// Callback prototype
BOOLEAN NTAPI EnumCallback(
    PLDR_DATA_TABLE_ENTRY Module,
    PVOID Context,
    BOOLEAN *Stop
){
    wprintf(L"Base: %p\n",Module->DllBase);

    return TRUE; // continue enumeration
}

int main() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll) return 1;

    LdrEnumerateLoadedModules_t LdrEnumerateLoadedModules =
        (LdrEnumerateLoadedModules_t)GetProcAddress(
            ntdll,
            "LdrEnumerateLoadedModules"
        );

    if(!LdrEnumerateLoadedModules)
        return 1;

    LdrEnumerateLoadedModules(0, EnumCallback, NULL);

    return 0;
}
