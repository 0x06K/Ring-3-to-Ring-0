#include <windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI *pEnclaveUnsealData)(
    const VOID* ProtectedBlob,
    UINT32 ProtectedBlobSize,
    VOID* DecryptedData,
    UINT32 DecryptedDataBufferSize,
    UINT32* DecryptedDataSize,
    VOID* SealingIdentity,
    UINT32* SealingIdentitySize
);

int main() {
    printf("=== EnclaveUnsealData ===\n");
    
    HMODULE vertdll = LoadLibraryA("vertdll.dll");
    pEnclaveUnsealData EnclaveUnsealData = 
        (pEnclaveUnsealData)GetProcAddress(vertdll, "EnclaveUnsealData");
    
    BYTE protectedBlob[1024];
    BYTE decryptedData[128];
    UINT32 decryptedSize;
    BYTE sealingIdentity[256];
    UINT32 identitySize;
    
    HRESULT result = EnclaveUnsealData(protectedBlob, 1024, decryptedData, 128, 
                                       &decryptedSize, sealingIdentity, &identitySize);
    
    printf("Return Value (HRESULT): 0x%08lx\n", result);
    printf("Protected Blob Address: 0x%p\n", protectedBlob);
    printf("Protected Blob Size: %lu\n", 1024);
    printf("Decrypted Data Address: 0x%p\n", decryptedData);
    printf("Decrypted Size: %lu\n", decryptedSize);
    printf("Identity Size: %lu\n", identitySize);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}