#include <windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI *pEnclaveGetEnclaveInformation)(
    UINT32 InformationSize,
    VOID* EnclaveInformation
);

int main() {
    printf("=== EnclaveGetEnclaveInformation ===\n");
    
    HMODULE vertdll = LoadLibraryA("vertdll.dll");
    pEnclaveGetEnclaveInformation EnclaveGetEnclaveInformation = 
        (pEnclaveGetEnclaveInformation)GetProcAddress(vertdll, "EnclaveGetEnclaveInformation");
    
    BYTE enclaveInfo[1024];
    UINT32 infoSize = 1024;
    
    HRESULT result = EnclaveGetEnclaveInformation(infoSize, enclaveInfo);
    
    printf("Return Value (HRESULT): 0x%08lx\n", result);
    printf("Information Size: %lu\n", infoSize);
    printf("Enclave Information Address: 0x%p\n", enclaveInfo);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}