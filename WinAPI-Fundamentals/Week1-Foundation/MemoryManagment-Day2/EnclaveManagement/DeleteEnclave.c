#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== DeleteEnclave ===\n");
    
    LPVOID enclave = CreateEnclave(GetCurrentProcess(), NULL, 1024 * 1024, 4096, 
                                   ENCLAVE_TYPE_VBS, NULL, 0, NULL);
    
    BOOL result = DeleteEnclave(enclave);
    
    printf("Return Value: %d\n", result);
    printf("Enclave Address: 0x%p\n", enclave);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}