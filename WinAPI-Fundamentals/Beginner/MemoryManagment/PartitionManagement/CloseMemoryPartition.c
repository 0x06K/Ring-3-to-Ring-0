#include <windows.h>
#include <stdio.h>

typedef HANDLE (WINAPI *pCreateMemoryPartition)(HANDLE, DWORD, PVOID, ULONG);

int main() {
    printf("=== CloseMemoryPartition ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pCreateMemoryPartition CreateMemoryPartition = 
        (pCreateMemoryPartition)GetProcAddress(kernelbase, "CreateMemoryPartition");
    
    HANDLE partition = CreateMemoryPartition(NULL, MAXIMUM_ALLOWED, NULL, 0);
    
    BOOL result = CloseHandle(partition);
    
    printf("Return Value: %d\n", result);
    printf("Partition Handle: 0x%p\n", partition);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}