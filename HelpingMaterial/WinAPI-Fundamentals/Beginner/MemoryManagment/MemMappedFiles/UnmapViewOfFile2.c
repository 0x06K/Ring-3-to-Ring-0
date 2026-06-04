#include <windows.h>
#include <stdio.h>

typedef BOOL (WINAPI *pUnmapViewOfFile2)(
    HANDLE Process,
    PVOID BaseAddress,
    ULONG UnmapFlags
);

int main() {
    printf("=== UnmapViewOfFile2 ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pUnmapViewOfFile2 UnmapViewOfFile2 = (pUnmapViewOfFile2)GetProcAddress(kernelbase, "UnmapViewOfFile2");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    LPVOID pView = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
    BOOL result = UnmapViewOfFile2(GetCurrentProcess(), pView, 0);
    
    printf("Return Value: %d\n", result);
    printf("View Address: 0x%p\n", pView);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}