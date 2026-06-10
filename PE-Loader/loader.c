#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef NTSTATUS (NTAPI *pNtUnmapViewOfSection)(HANDLE, PVOID);
typedef BOOL (WINAPI *PDLL_MAIN)(HINSTANCE, DWORD, LPVOID);
typedef void (WINAPI *PIMAGE_TLS_CALLBACK)(PVOID, DWORD, PVOID);

DWORD GetSectionProtection(DWORD characteristics) {
    DWORD protect = 0;
    
    if (characteristics & IMAGE_SCN_MEM_EXECUTE) {
        if (characteristics & IMAGE_SCN_MEM_READ) {
            if (characteristics & IMAGE_SCN_MEM_WRITE) {
                protect = PAGE_EXECUTE_READWRITE;
            } else {
                protect = PAGE_EXECUTE_READ;
            }
        } else if (characteristics & IMAGE_SCN_MEM_WRITE) {
            protect = PAGE_EXECUTE_WRITECOPY;
        } else {
            protect = PAGE_EXECUTE;
        }
    } else if (characteristics & IMAGE_SCN_MEM_READ) {
        if (characteristics & IMAGE_SCN_MEM_WRITE) {
            protect = PAGE_READWRITE;
        } else {
            protect = PAGE_READONLY;
        }
    } else if (characteristics & IMAGE_SCN_MEM_WRITE) {
        protect = PAGE_WRITECOPY;
    } else {
        protect = PAGE_NOACCESS;
    }
    
    return protect;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PE-File.exe>\n", argv[0]);
        return 1;
    }
    
    char* filename = argv[1];
    LPVOID base = NULL;
    LPVOID allocatedBase = NULL;
    
    
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return 1;
    }
    
    HANDLE hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (!hMap) {
        CloseHandle(hFile);
        return 1;
    }
    
    base = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (!base) {
        CloseHandle(hMap);
        CloseHandle(hFile);
        return 1;
    }
    
    CloseHandle(hMap);
    CloseHandle(hFile);
    
    
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)base;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        UnmapViewOfFile(base);
        return 1;
    }
    
    IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)((BYTE*)base + dosHeader->e_lfanew);
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE) {
        UnmapViewOfFile(base);
        return 1;
    }
    
    
    allocatedBase = VirtualAlloc(
        (LPVOID)ntHeader->OptionalHeader.ImageBase,
        ntHeader->OptionalHeader.SizeOfImage,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );
    
    if (!allocatedBase) {
        allocatedBase = VirtualAlloc(
            NULL,
            ntHeader->OptionalHeader.SizeOfImage,
            MEM_RESERVE | MEM_COMMIT,
            PAGE_EXECUTE_READWRITE
        );
    }
    
    if (!allocatedBase) {
        UnmapViewOfFile(base);
        return 1;
    }
    
    
    memcpy(allocatedBase, base, ntHeader->OptionalHeader.SizeOfHeaders);
    
    
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeader);
    for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++) {
        if (section[i].SizeOfRawData > 0) {
            memcpy(
                (BYTE*)allocatedBase + section[i].VirtualAddress,
                (BYTE*)base + section[i].PointerToRawData,
                section[i].SizeOfRawData
            );
        }
    }
    
    
    ULONGLONG delta = (ULONGLONG)allocatedBase - ntHeader->OptionalHeader.ImageBase;
    if (delta != 0) {
        IMAGE_DATA_DIRECTORY relocDir = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
        if (relocDir.VirtualAddress != 0) {
            IMAGE_BASE_RELOCATION* reloc = (IMAGE_BASE_RELOCATION*)((BYTE*)allocatedBase + relocDir.VirtualAddress);
            
            while (reloc->VirtualAddress != 0 && reloc->SizeOfBlock != 0) {
                DWORD numEntries = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
                WORD* relocData = (WORD*)((BYTE*)reloc + sizeof(IMAGE_BASE_RELOCATION));
                
                for (DWORD i = 0; i < numEntries; i++) {
                    int type = relocData[i] >> 12;
                    int offset = relocData[i] & 0xFFF;
                    
                    if (type == IMAGE_REL_BASED_DIR64) {
                        ULONGLONG* patchAddr = (ULONGLONG*)((BYTE*)allocatedBase + reloc->VirtualAddress + offset);
                        *patchAddr += delta;
                    } else if (type == IMAGE_REL_BASED_HIGHLOW) {
                        DWORD* patchAddr = (DWORD*)((BYTE*)allocatedBase + reloc->VirtualAddress + offset);
                        *patchAddr += (DWORD)delta;
                    }
                }
                
                reloc = (IMAGE_BASE_RELOCATION*)((BYTE*)reloc + reloc->SizeOfBlock);
            }
        }
    }
    
    
    IMAGE_DATA_DIRECTORY importDir = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (importDir.VirtualAddress != 0) {
        IMAGE_IMPORT_DESCRIPTOR* importDesc = (IMAGE_IMPORT_DESCRIPTOR*)((BYTE*)allocatedBase + importDir.VirtualAddress);
        
        while (importDesc->Name != 0) {
            char* dllName = (char*)((BYTE*)allocatedBase + importDesc->Name);
            HMODULE hModule = LoadLibraryA(dllName);
            
            if (hModule) {
                ULONGLONG* thunkRef;
                ULONGLONG* funcRef;
                
                if (importDesc->OriginalFirstThunk) {
                    thunkRef = (ULONGLONG*)((BYTE*)allocatedBase + importDesc->OriginalFirstThunk);
                    funcRef = (ULONGLONG*)((BYTE*)allocatedBase + importDesc->FirstThunk);
                } else {
                    thunkRef = (ULONGLONG*)((BYTE*)allocatedBase + importDesc->FirstThunk);
                    funcRef = (ULONGLONG*)((BYTE*)allocatedBase + importDesc->FirstThunk);
                }
                
                while (*thunkRef) {
                    if (IMAGE_SNAP_BY_ORDINAL(*thunkRef)) {
                        *funcRef = (ULONGLONG)GetProcAddress(hModule, (LPCSTR)IMAGE_ORDINAL(*thunkRef));
                    } else {
                        IMAGE_IMPORT_BY_NAME* importByName = (IMAGE_IMPORT_BY_NAME*)((BYTE*)allocatedBase + (*thunkRef));
                        *funcRef = (ULONGLONG)GetProcAddress(hModule, importByName->Name);
                    }
                    thunkRef++;
                    funcRef++;
                }
            }
            
            importDesc++;
        }
    }
    
    
    IMAGE_DATA_DIRECTORY tlsDir = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS];
    if (tlsDir.VirtualAddress != 0) {
        IMAGE_TLS_DIRECTORY* tlsDirectory = (IMAGE_TLS_DIRECTORY*)((BYTE*)allocatedBase + tlsDir.VirtualAddress);
        PIMAGE_TLS_CALLBACK* callback = (PIMAGE_TLS_CALLBACK*)(tlsDirectory->AddressOfCallBacks);
        
        if (callback) {
            while (*callback) {
                (*callback)((PVOID)allocatedBase, DLL_PROCESS_ATTACH, NULL);
                callback++;
            }
        }
    }
    
    
    for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++) {
        DWORD protect = GetSectionProtection(section[i].Characteristics);
        DWORD oldProtect;
        
        VirtualProtect(
            (BYTE*)allocatedBase + section[i].VirtualAddress,
            section[i].Misc.VirtualSize,
            protect,
            &oldProtect
        );
    }
    
    
    ULONGLONG entryPoint = (ULONGLONG)allocatedBase + ntHeader->OptionalHeader.AddressOfEntryPoint;
    
    
    PDLL_MAIN dllMain = (PDLL_MAIN)entryPoint;
    dllMain((HINSTANCE)allocatedBase, DLL_PROCESS_ATTACH, NULL);
    

    UnmapViewOfFile(base);
    printf("\nExecution Finished\n");
    return 0;
}