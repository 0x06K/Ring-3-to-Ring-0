#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main() {
    HANDLE hProc = GetCurrentProcess(); // current process; can replace with other PID handle
    HMODULE modules[1024];
    DWORD needed;

    if(EnumProcessModules(hProc, modules, sizeof(modules), &needed)) {
        int count = needed / sizeof(HMODULE);
        for(int i = 0; i < count; i++){
            char path[MAX_PATH] = {0};
            if(GetModuleFileNameExA(hProc, modules[i], path, MAX_PATH))
                printf("GetModuleFileNameEx: %s\n", path);
        }
    }

    return 0;
}
