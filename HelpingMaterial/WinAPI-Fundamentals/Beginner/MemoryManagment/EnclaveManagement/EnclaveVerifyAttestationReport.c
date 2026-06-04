#include <windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI *pEnclaveVerifyAttestationReport)(
    UINT32 EnclaveType,
    const VOID* Report,
    UINT32 ReportSize
);

int main() {
    printf("=== EnclaveVerifyAttestationReport ===\n");
    
    HMODULE vertdll = LoadLibraryA("vertdll.dll");
    pEnclaveVerifyAttestationReport EnclaveVerifyAttestationReport = 
        (pEnclaveVerifyAttestationReport)GetProcAddress(vertdll, "EnclaveVerifyAttestationReport");
    
    UINT32 enclaveType = ENCLAVE_TYPE_VBS;
    BYTE report[4096];
    UINT32 reportSize = 4096;
    
    HRESULT result = EnclaveVerifyAttestationReport(enclaveType, report, reportSize);
    
    printf("Return Value (HRESULT): 0x%08lx\n", result);
    printf("Enclave Type: 0x%08lx\n", enclaveType);
    printf("Report Address: 0x%p\n", report);
    printf("Report Size: %lu\n", reportSize);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}