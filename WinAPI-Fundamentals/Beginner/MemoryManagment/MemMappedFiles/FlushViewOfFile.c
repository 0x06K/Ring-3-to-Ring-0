#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== FlushViewOfFile ===\n");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    LPVOID pView = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
    BOOL result = FlushViewOfFile(pView, 4096);
    
    printf("Return Value: %d\n", result);
    printf("View Address: 0x%p\n", pView);
    printf("Bytes to Flush: 4096\n");
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("File Handle: 0x%p\n", hFile);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}