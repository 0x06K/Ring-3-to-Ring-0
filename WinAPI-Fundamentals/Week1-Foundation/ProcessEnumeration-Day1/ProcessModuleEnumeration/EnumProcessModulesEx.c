#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main(){
    HANDLE hProc=GetCurrentProcess();
    HMODULE modules[1024];
    DWORD needed;

    if(EnumProcessModulesEx(hProc,modules,sizeof(modules),&needed,LIST_MODULES_ALL)){
        int count=needed/sizeof(HMODULE);
        for(int i = 0; i < count; i++){
            printf("HMODULE: %p\n", modules[i]);
        }
    }
    return 0;
}
