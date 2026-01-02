#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CallEnclave ===\n");
    
    LPVOID enclave = CreateEnclave(GetCurrentProcess(), NULL, 1024 * 1024, 4096, 
                                   ENCLAVE_TYPE_VBS, NULL, 0, NULL);
    LPENCLAVE_ROUTINE routine = (LPENCLAVE_ROUTINE)enclave;
    LPVOID parameter = NULL;
    BOOL waitForThread = TRUE;
    
    BOOL result = CallEnclave(routine, parameter, waitForThread, NULL);
    
    printf("Return Value: %d\n", result);
    printf("Routine Address: 0x%p\n", routine);
    printf("Parameter: 0x%p\n", parameter);
    printf("Wait For Thread: %d\n", waitForThread);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}