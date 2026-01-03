#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main(){
    HMODULE modules[1024];
    DWORD needed;

    if(EnumProcessModules(GetCurrentProcess(), modules, sizeof(modules), &needed)){
        int count = needed / sizeof(HMODULE);
        for(int i = 0; i < count; i++){
            printf("HMODULE: %p\n", modules[i]);
        }
    }
    return 0;
}