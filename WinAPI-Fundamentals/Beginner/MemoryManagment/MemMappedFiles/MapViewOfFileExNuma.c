#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== MapViewOfFileExNuma ===\n");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    LPVOID pDesired = (LPVOID)0x10000000;
    LPVOID pView = MapViewOfFileExNuma(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096, pDesired, 0);
    
    printf("View Address: 0x%p\n", pView);
    printf("Desired Address: 0x%p\n", pDesired);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("File Handle: 0x%p\n", hFile);
    printf("NUMA Node: 0\n");
    printf("Size: 4096\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}