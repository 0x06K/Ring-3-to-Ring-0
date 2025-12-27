
## **WEEK 1: Foundation APIs**

### Day 1: Process Enumeration

**Process Enumerator (Snapshot)**

* **Goal:** List all running processes using the standard snapshot method.
* **APIs:** `CreateToolhelp32Snapshot`, `Process32First`, `Process32Next`

**Process Enumerator (PSAPI)**

* **Goal:** Enumerate PIDs using a raw array to avoid snapshot handles.
* **APIs:** `EnumProcesses`, `OpenProcess`, `GetModuleBaseName`

**Process Enumerator (Native)**

* **Goal:** Bypass Win32 hooks by calling the kernel's query function directly.
* **APIs:** `NtQuerySystemInformation`, `GetProcAddress`, `GetModuleHandle`

**Process Enumerator (WMI)**

* **Goal:** Use management queries to blend with administrative traffic.
* **APIs:** `CoInitializeEx`, `IWbemServices::ExecQuery`, `IEnumWbemClassObject`

**Process Enumerator (CSRSS)**

* **Goal:** Query the process subsystem directly via ALPC/internal caches.
* **APIs:** `CsrGetProcessId`, `NtConnectPort`
