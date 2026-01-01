#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateFileMappingA ===\n");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, "MyMapping");
    
    printf("File Handle: 0x%p\n", hFile);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("Mapping Name: MyMapping\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}