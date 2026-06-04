#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main() {
    HANDLE hProc = GetCurrentProcess();
    HMODULE modules[1024];
    DWORD needed;

    if(EnumProcessModules(hProc, modules, sizeof(modules), &needed)) {
        int count = needed / sizeof(HMODULE);

        for(int i = 0; i < count; i++) {
            char name[MAX_PATH] = {0};
            if(GetModuleBaseNameA(hProc, modules[i], name, MAX_PATH))
                printf("Module base name: %s\n", name);
        }
    }
    return 0;
}
