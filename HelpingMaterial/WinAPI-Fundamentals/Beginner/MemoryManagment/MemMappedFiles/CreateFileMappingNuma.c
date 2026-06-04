#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateFileMappingNuma ===\n");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingNuma(hFile, NULL, PAGE_READWRITE, 0, 4096, "MyNumaMapping", 0);
    
    printf("File Handle: 0x%p\n", hFile);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("Mapping Name: MyNumaMapping\n");
    printf("NUMA Node: 0\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}