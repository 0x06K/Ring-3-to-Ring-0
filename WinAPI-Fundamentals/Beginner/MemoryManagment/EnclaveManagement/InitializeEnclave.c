#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== InitializeEnclave ===\n");
    
    LPVOID enclave = CreateEnclave(GetCurrentProcess(), NULL, 1024 * 1024, 4096, 
                                   ENCLAVE_TYPE_VBS, NULL, 0, NULL);
    LPVOID entryPoint = enclave;
    LPCVOID enclaveInfo = NULL;
    DWORD infoLength = 0;
    
    BOOL result = InitializeEnclave(GetCurrentProcess(), enclave, entryPoint, 
                                    enclaveInfo, infoLength, NULL);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Enclave Address: 0x%p\n", enclave);
    printf("Entry Point: 0x%p\n", entryPoint);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}