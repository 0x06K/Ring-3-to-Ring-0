#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateFileMappingW ===\n");
    
    HANDLE hFile = CreateFileW(L"test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingW(hFile, NULL, PAGE_READWRITE, 0, 4096, L"MyMapping");
    
    printf("File Handle: 0x%p\n", hFile);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("Mapping Name: MyMapping\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}