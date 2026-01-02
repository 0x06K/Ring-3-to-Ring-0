#include <windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI *pEnclaveSealData)(
    const VOID* DataToEncrypt,
    UINT32 DataToEncryptSize,
    UINT32 EnclaveSealingFlags,
    VOID* ProtectedBlob,
    UINT32 ProtectedBlobSize,
    VOID* ProtectedBlobOutBuffer,
    UINT32* RequiredProtectedBlobOutSize
);

int main() {
    printf("=== EnclaveSealData ===\n");
    
    HMODULE vertdll = LoadLibraryA("vertdll.dll");
    pEnclaveSealData EnclaveSealData = 
        (pEnclaveSealData)GetProcAddress(vertdll, "EnclaveSealData");
    
    BYTE dataToEncrypt[128] = "SecretData";
    BYTE protectedBlob[1024];
    BYTE outputBuffer[1024];
    UINT32 requiredSize;
    
    HRESULT result = EnclaveSealData(dataToEncrypt, 128, 0, protectedBlob, 1024, 
                                     outputBuffer, &requiredSize);
    
    printf("Return Value (HRESULT): 0x%08lx\n", result);
    printf("Data Address: 0x%p\n", dataToEncrypt);
    printf("Data Size: %lu\n", 128);
    printf("Protected Blob Address: 0x%p\n", protectedBlob);
    printf("Output Buffer Address: 0x%p\n", outputBuffer);
    printf("Required Size: %lu\n", requiredSize);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}