#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== OpenFileMappingA ===\n");
    
    HANDLE hMapping = OpenFileMappingA(FILE_MAP_READ, FALSE, "MyMapping");
    
    printf("Mapping Handle: 0x%p\n", hMapping);
    printf("Mapping Name: MyMapping\n");
    printf("Desired Access: FILE_MAP_READ\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}