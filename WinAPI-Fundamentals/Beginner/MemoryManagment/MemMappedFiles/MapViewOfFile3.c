#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pMapViewOfFile3)(
    HANDLE FileMapping,
    HANDLE Process,
    PVOID BaseAddress,
    ULONG64 Offset,
    SIZE_T ViewSize,
    ULONG AllocationType,
    ULONG PageProtection,
    PVOID ExtendedParameters,
    ULONG ParameterCount
);

int main() {
    printf("=== MapViewOfFile3 ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pMapViewOfFile3 MapViewOfFile3 = (pMapViewOfFile3)GetProcAddress(kernelbase, "MapViewOfFile3");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    PVOID pView = MapViewOfFile3(hMapping, GetCurrentProcess(), NULL, 0, 4096, 0, PAGE_READWRITE, NULL, 0);
    
    printf("View Address: 0x%p\n", pView);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("File Handle: 0x%p\n", hFile);
    printf("Size: 4096\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}