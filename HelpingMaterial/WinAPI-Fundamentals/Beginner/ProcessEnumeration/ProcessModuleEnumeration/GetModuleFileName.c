#include <windows.h>
#include <stdio.h>

int main() {
    char exePath[MAX_PATH];

    if(GetModuleFileNameA(NULL, exePath, MAX_PATH))
        printf("GetModuleFileName: %s\n", exePath);

    return 0;
}
