#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== TerminateEnclave ===\n");
    
    LPVOID enclave = CreateEnclave(GetCurrentProcess(), NULL, 1024 * 1024, 4096, 
                                   ENCLAVE_TYPE_VBS, NULL, 0, NULL);
    BOOL waitForThread = TRUE;
    
    BOOL result = TerminateEnclave(enclave, waitForThread);
    
    printf("Return Value: %d\n", result);
    printf("Enclave Address: 0x%p\n", enclave);
    printf("Wait For Thread: %d\n", waitForThread);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}