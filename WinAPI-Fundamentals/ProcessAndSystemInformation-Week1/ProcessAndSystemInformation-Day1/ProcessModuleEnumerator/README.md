Only **user-mode**, only **module-related**, grouped exactly as requested.

---

# 📦 Module Enumeration APIs (Categorized)

## 🟦 WinAPI (High-level, documented)

Used by normal applications and tools.

```
CreateToolhelp32Snapshot
Module32First
Module32Next
```

---

## 🟩 PSAPI (Process Status API)

Used for process & module inspection through handles.

```
EnumProcessModules
EnumProcessModulesEx
GetModuleBaseNameA
GetModuleFileNameEx
GetModuleInformation
```

---

## 🟥 Native / NT API (Undocumented / Low-level)

Used internally by Windows, debuggers, EDRs, and advanced tools.

```
NtQueryInformationProcess
LdrEnumerateLoadedModules
NtQueryVirtualMemory
NtWow64QueryInformationProcess64
NtWow64ReadVirtualMemory64
```
