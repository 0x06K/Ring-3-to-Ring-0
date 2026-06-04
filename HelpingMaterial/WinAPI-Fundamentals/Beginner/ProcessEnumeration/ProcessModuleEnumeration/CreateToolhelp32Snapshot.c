#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

int main(void){
    DWORD pid = GetCurrentProcessId();
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);

    if(Module32First(snap, &me)){
        do{
            printf("ProcessID: %lu\n", me.th32ProcessID);
            printf("Base     : %p\n", me.modBaseAddr);
            printf("Size     : %lu\n", me.modBaseSize);
            printf("Module   : %s\n", me.szModule);
            printf("Path     : %s\n", me.szExePath);
            printf("====================================\n");
        } while(Module32Next(snap, &me));
    }

    CloseHandle(snap);
    return 0;
}
