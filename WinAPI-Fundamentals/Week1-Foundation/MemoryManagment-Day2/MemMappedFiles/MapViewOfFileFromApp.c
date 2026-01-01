#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== MapViewOfFileFromApp ===\n");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    PVOID pView = MapViewOfFileFromApp(hMapping, FILE_MAP_ALL_ACCESS, 0, 4096);
    
    printf("View Address: 0x%p\n", pView);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("File Handle: 0x%p\n", hFile);
    printf("Size: 4096\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}