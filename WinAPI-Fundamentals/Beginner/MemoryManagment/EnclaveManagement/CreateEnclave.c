#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateEnclave ===\n");
    
    LPVOID baseAddress = NULL;
    SIZE_T size = 1024 * 1024;
    SIZE_T initialCommit = 4096;
    DWORD enclaveType = ENCLAVE_TYPE_VBS;
    LPCVOID enclaveInfo = NULL;
    DWORD infoLength = 0;
    
    LPVOID result = CreateEnclave(GetCurrentProcess(), baseAddress, size, initialCommit, 
                                  enclaveType, enclaveInfo, infoLength, NULL);
    
    printf("Return Address: 0x%p\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Size: %zu\n", size);
    printf("Initial Commit: %zu\n", initialCommit);
    printf("Enclave Type: 0x%08lx\n", enclaveType);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}