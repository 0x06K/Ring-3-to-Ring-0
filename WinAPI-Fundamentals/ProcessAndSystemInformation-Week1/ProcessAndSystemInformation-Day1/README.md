
## **WEEK 1: Foundation APIs**

### **Day 1: Process & System Information**
**Process Enumerator** - List all running processes
   - APIs: `CreateToolhelp32Snapshot`, `Process32First`, `Process32Next`

2. **Process Info Viewer** - Get detailed info about a specific process
   - APIs: `OpenProcess`, `GetProcessId`, `GetProcessImageFileNameA`

3. **Module Enumerator** - List all DLLs loaded in a process
   - APIs: `CreateToolhelp32Snapshot`, `Module32First`, `Module32Next`

4. **Thread Enumerator** - List all threads in a process
   - APIs: `CreateToolhelp32Snapshot`, `Thread32First`, `Thread32Next`

5. **System Info Printer** - Get system information
   - APIs: `GetSystemInfo`, `GetComputerNameA`, `GetVersionExA`

---

### **Day 2: Memory Management**
6. **Basic Memory Allocator** - Allocate/free memory in your process
   - APIs: `VirtualAlloc`, `VirtualFree`

7. **Memory Protection Changer** - Change memory permissions
   - APIs: `VirtualAlloc`, `VirtualProtect`

8. **Memory Query Tool** - Query memory region information
   - APIs: `VirtualQuery`, `VirtualQueryEx`

9. **Heap Allocator** - Use heap APIs
   - APIs: `HeapCreate`, `HeapAlloc`, `HeapFree`, `HeapDestroy`

10. **Memory Pattern Search** - Search for byte patterns in memory
    - APIs: `VirtualQuery`, `ReadProcessMemory`

---

### **Day 3: Thread Management**
11. **Simple Thread Creator** - Create threads in your process
    - APIs: `CreateThread`, `WaitForSingleObject`, `CloseHandle`

12. **Thread Suspender** - Suspend and resume threads
    - APIs: `OpenThread`, `SuspendThread`, `ResumeThread`

13. **Thread Context Reader** - Get thread register values
    - APIs: `GetThreadContext`, `SetThreadContext`

14. **Thread Priority Manager** - Change thread priorities
    - APIs: `SetThreadPriority`, `GetThreadPriority`

15. **Thread Stack Walker** - Walk thread call stack
    - APIs: `StackWalk64`, `SymInitialize`, `SymGetSymFromAddr64`

---

### **Day 4: Process Handles & Manipulation**
16. **Process Handle Opener** - Open handles to other processes
    - APIs: `OpenProcess`, `CloseHandle`

17. **Process Terminator** - Kill processes
    - APIs: `OpenProcess`, `TerminateProcess`

18. **Process Creator** - Launch new processes
    - APIs: `CreateProcessA`, `CreateProcessW`

19. **Process Debugger Checker** - Detect if process is being debugged
    - APIs: `IsDebuggerPresent`, `CheckRemoteDebuggerPresent`

20. **Parent Process Spoofer** - Create process with fake parent
    - APIs: `CreateProcess`, `InitializeProcThreadAttributeList`, `UpdateProcThreadAttribute`

---

### **Day 5: Remote Memory Operations**
21. **Remote Memory Reader** - Read memory from another process
    - APIs: `OpenProcess`, `ReadProcessMemory`

22. **Remote Memory Writer** - Write to another process
    - APIs: `OpenProcess`, `VirtualAllocEx`, `WriteProcessMemory`

23. **Remote Memory Allocator** - Allocate in another process
    - APIs: `VirtualAllocEx`, `VirtualFreeEx`

24. **Remote Memory Protection** - Change permissions in another process
    - APIs: `VirtualProtectEx`

25. **Remote Pattern Patcher** - Find and patch bytes in another process
    - APIs: `VirtualQueryEx`, `ReadProcessMemory`, `WriteProcessMemory`

---

### **Day 6: Dynamic Loading & Symbols**
26. **DLL Loader** - Load DLLs at runtime
    - APIs: `LoadLibraryA`, `GetProcAddress`, `FreeLibrary`

27. **Function Address Finder** - Find function addresses in DLLs
    - APIs: `GetModuleHandleA`, `GetProcAddress`

28. **Export Table Parser** - Parse DLL exports manually
    - APIs: `GetModuleHandleA`, manual PE parsing

29. **Import Table Parser** - Parse executable imports
    - APIs: Manual PE parsing

30. **Module Base Address Finder** - Find loaded module addresses
    - APIs: `GetModuleHandleA`, `GetModuleHandleExA`

---

### **Day 7: Remote Thread Execution**
31. **Remote Thread Creator** - Create thread in another process
    - APIs: `CreateRemoteThread`, `WaitForSingleObject`

32. **Remote MessageBox** - Make another process show MessageBox
    - APIs: `CreateRemoteThread`, `GetProcAddress`, `VirtualAllocEx`

33. **Basic DLL Injector** - Full DLL injection
    - APIs: All from previous days combined

34. **Thread Hijacker** - Hijack existing thread
    - APIs: `SuspendThread`, `GetThreadContext`, `SetThreadContext`, `ResumeThread`

35. **APC Queue Injector** - Inject via QueueUserAPC
    - APIs: `QueueUserAPC`, `OpenThread`, `VirtualAllocEx`

---
