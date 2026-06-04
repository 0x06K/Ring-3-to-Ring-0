#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== IsEnclaveTypeSupported ===\n");
    
    DWORD enclaveType = ENCLAVE_TYPE_VBS;
    
    BOOL result = IsEnclaveTypeSupported(enclaveType);
    
    printf("Return Value: %d\n", result);
    printf("Enclave Type: ENCLAVE_TYPE_VBS (0x%08lx)\n", enclaveType);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}