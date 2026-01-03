#include <windows.h>
#include <stdio.h>

typedef enum _MEMORY_PRIORITY {
    MEMORY_PRIORITY_VERY_LOW = 1,
    MEMORY_PRIORITY_LOW = 2,
    MEMORY_PRIORITY_MEDIUM = 3,
    MEMORY_PRIORITY_BELOW_NORMAL = 4,
    MEMORY_PRIORITY_NORMAL = 5
} MEMORY_PRIORITY;

typedef struct _MEMORY_PRIORITY_INFORMATION {
    MEMORY_PRIORITY MemoryPriority;
} MEMORY_PRIORITY_INFORMATION;

int main() {
    printf("=== SetProcessInformation (ProcessMemoryPriority) ===\n");
    
    MEMORY_PRIORITY_INFORMATION memInfo;
    memInfo.MemoryPriority = MEMORY_PRIORITY_NORMAL;
    
    BOOL result = SetProcessInformation(GetCurrentProcess(), ProcessMemoryPriority, 
                                        &memInfo, sizeof(memInfo));
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Memory Priority: %d\n", memInfo.MemoryPriority);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}