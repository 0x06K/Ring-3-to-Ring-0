#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main() {
    HANDLE hProc = GetCurrentProcess();
    HMODULE modules[1024];
    DWORD needed;

    if(EnumProcessModules(hProc, modules, sizeof(modules), &needed)) {
        int count = needed / sizeof(HMODULE);
        for(int i = 0; i < count; i++){
            MODULEINFO mi = {0};
            if(GetModuleInformation(hProc, modules[i], &mi, sizeof(mi))){
                printf("Module Base: %p\n", mi.lpBaseOfDll);
                printf("Size       : 0x%X\n", mi.SizeOfImage);
                printf("EntryPoint : %p\n\n", mi.EntryPoint);
            }
        }
    }
    return 0;
}
