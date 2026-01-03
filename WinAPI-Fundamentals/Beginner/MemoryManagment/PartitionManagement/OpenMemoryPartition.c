#include <windows.h>
#include <stdio.h>

typedef HANDLE (WINAPI *pOpenMemoryPartition)(
    DWORD DesiredAccess,
    BOOL InheritHandle,
    LPCWSTR PartitionName
);

int main() {
    printf("=== OpenMemoryPartition ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pOpenMemoryPartition OpenMemoryPartition = 
        (pOpenMemoryPartition)GetProcAddress(kernelbase, "OpenMemoryPartition");
    
    LPCWSTR partitionName = L"MyPartition";
    
    HANDLE result = OpenMemoryPartition(MAXIMUM_ALLOWED, FALSE, partitionName);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Desired Access: MAXIMUM_ALLOWED\n");
    printf("Inherit Handle: FALSE\n");
    printf("Partition Name: %ls\n", partitionName);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}