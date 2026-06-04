#include <windows.h>
#include <stdio.h>

typedef HANDLE (WINAPI *pCreateMemoryPartition)(
    HANDLE ParentPartitionHandle,
    DWORD DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    ULONG Flags
);

int main() {
    printf("=== CreateMemoryPartition ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pCreateMemoryPartition CreateMemoryPartition = 
        (pCreateMemoryPartition)GetProcAddress(kernelbase, "CreateMemoryPartition");
    
    HANDLE result = CreateMemoryPartition(NULL, MAXIMUM_ALLOWED, NULL, 0);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Parent Partition: 0x%p\n", (HANDLE)NULL);
    printf("Desired Access: MAXIMUM_ALLOWED\n");
    printf("Flags: %lu\n", 0UL);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}