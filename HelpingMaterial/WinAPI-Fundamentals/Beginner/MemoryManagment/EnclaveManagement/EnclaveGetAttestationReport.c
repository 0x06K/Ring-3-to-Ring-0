#include <windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI *pEnclaveGetAttestationReport)(
    const UINT8* EnclaveData,
    const VOID* Report,
    UINT32 BufferSize,
    UINT32* OutputSize
);

int main() {
    printf("=== EnclaveGetAttestationReport ===\n");
    
    HMODULE vertdll = LoadLibraryA("vertdll.dll");
    pEnclaveGetAttestationReport EnclaveGetAttestationReport = 
        (pEnclaveGetAttestationReport)GetProcAddress(vertdll, "EnclaveGetAttestationReport");
    
    UINT8 enclaveData[32] = {0};
    BYTE reportBuffer[4096];
    UINT32 bufferSize = 4096;
    UINT32 outputSize;
    
    HRESULT result = EnclaveGetAttestationReport(enclaveData, reportBuffer, bufferSize, &outputSize);
    
    printf("Return Value (HRESULT): 0x%08lx\n", result);
    printf("Enclave Data Address: 0x%p\n", enclaveData);
    printf("Report Buffer Address: 0x%p\n", reportBuffer);
    printf("Buffer Size: %lu\n", bufferSize);
    printf("Output Size: %lu\n", outputSize);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}