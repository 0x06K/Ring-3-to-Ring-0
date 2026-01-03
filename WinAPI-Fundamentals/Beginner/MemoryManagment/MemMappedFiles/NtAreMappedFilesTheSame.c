#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtAreMappedFilesTheSame)(
    PVOID Mapped1,
    PVOID Mapped2
);

int main() {
    printf("=== NtAreMappedFilesTheSame ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtAreMappedFilesTheSame NtAreMappedFilesTheSame = (pNtAreMappedFilesTheSame)GetProcAddress(ntdll, "NtAreMappedFilesTheSame");
    
    HANDLE hFile = CreateFileA("test.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, NULL);
    LPVOID pView1 = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
    LPVOID pView2 = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
    
    NTSTATUS status = NtAreMappedFilesTheSame(pView1, pView2);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Mapped Address 1: 0x%p\n", pView1);
    printf("Mapped Address 2: 0x%p\n", pView2);
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("File Handle: 0x%p\n", hFile);
    
    return 0;
}