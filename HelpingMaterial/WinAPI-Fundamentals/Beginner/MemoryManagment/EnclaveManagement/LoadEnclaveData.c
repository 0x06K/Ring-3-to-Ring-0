#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== LoadEnclaveData ===\n");
    
    LPVOID enclave = CreateEnclave(GetCurrentProcess(), NULL, 1024 * 1024, 4096, 
                                   ENCLAVE_TYPE_VBS, NULL, 0, NULL);
    LPVOID targetAddress = enclave;
    LPCVOID buffer = "EnclaveData";
    SIZE_T dataSize = 12;
    DWORD protect = PAGE_READWRITE;
    LPCVOID pageInfo = NULL;
    DWORD infoLength = 0;
    
    BOOL result = LoadEnclaveData(enclave, targetAddress, buffer, dataSize, 
                                  protect, pageInfo, infoLength, NULL, NULL);
    
    printf("Return Value: %d\n", result);
    printf("Enclave Address: 0x%p\n", enclave);
    printf("Target Address: 0x%p\n", targetAddress);
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Data Size: %zu\n", dataSize);
    printf("Protection: 0x%08lx\n", protect);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}