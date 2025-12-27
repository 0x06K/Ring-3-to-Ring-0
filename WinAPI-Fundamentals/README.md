## **Complete Windows API Mastery Program List**

Here's every program you should build to master Windows APIs for malware development:

---

## **WEEK 1: Foundation APIs**

### Day 1: Process Enumeration

### **Day 1: Process & System Information**
1. **Process Enumerator** - List all running processes
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

## **WEEK 2: Advanced Injection Techniques**

### **Day 8: PE Format Understanding**
36. **PE Header Parser** - Parse PE headers
    - Manual parsing of DOS header, NT headers, sections

37. **Section Enumerator** - List all PE sections
    - Manual PE parsing

38. **Import Resolver** - Resolve imports manually
    - Manual IAT parsing

39. **Export Finder** - Find exports manually
    - Manual EAT parsing

40. **Relocation Processor** - Process PE relocations
    - Manual relocation table parsing

---

### **Day 9: Reflective Loading**
41. **Manual DLL Mapper** - Load DLL without LoadLibrary
    - APIs: `VirtualAlloc`, manual PE mapping

42. **Reflective DLL Injector** - Inject DLL reflectively
    - Combine manual mapping with injection

43. **Memory Module Loader** - Load DLL from memory
    - No file on disk, pure memory loading

44. **Position Independent Code** - Write PIC shellcode
    - Manual assembly and relocation handling

45. **PE Injection** - Inject entire PE into process
    - Full PE loading from memory

---

### **Day 10: Process Hollowing & Doppelgänging**
46. **Process Hollower** - Classic process hollowing
    - APIs: `CreateProcess`, `NtUnmapViewOfSection`, `VirtualAllocEx`, `WriteProcessMemory`

47. **Process Doppelgänger** - Transaction-based hollowing
    - APIs: `CreateTransaction`, `CreateFileTransacted`, `RollbackTransaction`

48. **Process Ghosting** - Delete-pending file execution
    - APIs: `NtCreateFile`, `FILE_DELETE_ON_CLOSE`

49. **Process Herpaderping** - Overwrite image after mapping
    - APIs: `CreateProcess`, file mapping manipulation

50. **Early Bird Injection** - Inject before process starts
    - APIs: `CreateProcess` (suspended), `QueueUserAPC`

---

### **Day 11: Hooking Techniques**
51. **IAT Hook** - Hook Import Address Table
    - APIs: `VirtualProtect`, manual IAT patching

52. **Inline Hook** - Hook function prologue
    - APIs: `VirtualProtect`, assembly trampolines

53. **EAT Hook** - Hook Export Address Table
    - Manual EAT patching

54. **VTable Hook** - Hook C++ virtual tables
    - Memory manipulation

55. **SSDT Hook Reader** - Read System Service Descriptor Table
    - APIs: Driver required for actual hooking

---

### **Day 12: Syscalls & Unhooking**
56. **Direct Syscall Executor** - Call syscalls directly
    - Manual syscall assembly

57. **Syscall Number Extractor** - Extract syscall numbers from ntdll
    - Parse ntdll.dll functions

58. **NTDLL Unhooker** - Remove hooks from ntdll
    - APIs: `VirtualProtect`, `WriteProcessMemory`

59. **Fresh NTDLL Mapper** - Map clean ntdll.dll
    - APIs: `CreateFileMapping`, `MapViewOfFile`

60. **Heaven's Gate** - WOW64 to x64 syscall transition
    - Manual assembly for 32-bit to 64-bit jump

---

### **Day 13: AMSI & ETW Bypass**
61. **AMSI Patcher** - Patch AMSI in memory
    - APIs: `GetProcAddress`, `VirtualProtect`, memory patching

62. **AMSI Context Manipulation** - Modify AMSI context
    - Memory manipulation

63. **ETW Provider Disabler** - Disable ETW
    - APIs: `EventUnregister`, provider manipulation

64. **ETW Unhooker** - Remove ETW hooks
    - Memory patching

65. **PowerShell AMSI Bypass** - Bypass AMSI in PowerShell
    - Reflection-based patching

---

### **Day 14: Token & Privilege Manipulation**
66. **Token Viewer** - View process token info
    - APIs: `OpenProcessToken`, `GetTokenInformation`

67. **Privilege Enabler** - Enable token privileges
    - APIs: `OpenProcessToken`, `AdjustTokenPrivileges`

68. **Token Duplicator** - Duplicate process tokens
    - APIs: `DuplicateTokenEx`, `ImpersonateLoggedOnUser`

69. **Token Impersonator** - Impersonate other users
    - APIs: `ImpersonateLoggedOnUser`, `RevertToSelf`

70. **Token Stealer** - Steal SYSTEM token
    - APIs: `OpenProcess`, `OpenProcessToken`, `DuplicateTokenEx`

---

### **Day 15: Named Objects**
71. **Named Pipe Creator** - Create named pipes
    - APIs: `CreateNamedPipeA`, `ConnectNamedPipe`

72. **Named Pipe Client** - Connect to pipes
    - APIs: `CreateFileA`, `ReadFile`, `WriteFile`

73. **Mailslot Creator** - Create mailslots
    - APIs: `CreateMailslotA`, `GetMailslotInfo`

74. **Shared Memory Creator** - Create file mappings
    - APIs: `CreateFileMappingA`, `MapViewOfFile`

75. **Mutex Creator** - Create synchronization objects
    - APIs: `CreateMutexA`, `WaitForSingleObject`, `ReleaseMutex`

---

## **WEEK 3: Persistence & Evasion**

### **Day 16: Registry Persistence**
76. **Registry Key Creator** - Create Run keys
    - APIs: `RegCreateKeyExA`, `RegSetValueExA`

77. **Registry Key Modifier** - Modify existing keys
    - APIs: `RegOpenKeyExA`, `RegSetValueExA`

78. **Registry Key Enumerator** - List registry keys
    - APIs: `RegEnumKeyExA`, `RegEnumValueA`

79. **IFEO Hijacker** - Image File Execution Options
    - APIs: Registry manipulation

80. **AppInit DLL Installer** - Install via AppInit_DLLs
    - APIs: Registry manipulation

---

### **Day 17: Service Management**
81. **Service Creator** - Create Windows services
    - APIs: `OpenSCManagerA`, `CreateServiceA`

82. **Service Modifier** - Modify existing services
    - APIs: `OpenServiceA`, `ChangeServiceConfigA`

83. **Service Enumerator** - List all services
    - APIs: `EnumServicesStatusA`

84. **Service Controller** - Start/stop services
    - APIs: `StartServiceA`, `ControlService`

85. **Driver Loader** - Load kernel drivers
    - APIs: `OpenSCManagerA`, `CreateServiceA`, `StartServiceA`

---

### **Day 18: Scheduled Tasks**
86. **Task Scheduler Creator** - Create scheduled tasks
    - APIs: COM interfaces (ITaskService)

87. **Task Scheduler Modifier** - Modify tasks
    - APIs: COM interfaces

88. **WMI Event Creator** - WMI event subscriptions
    - APIs: WMI COM interfaces

89. **WMI Query Executor** - Execute WMI queries
    - APIs: COM interfaces

90. **COM Hijacker** - Hijack COM objects
    - APIs: Registry manipulation

---

### **Day 19: DLL Hijacking**
91. **DLL Search Order Exploiter** - DLL search order hijack
    - File system manipulation

92. **DLL Proxy Creator** - Create proxy DLLs
    - Forward exports to legitimate DLL

93. **DLL Sideloader** - Sideload malicious DLL
    - File placement

94. **Phantom DLL Hijacker** - Exploit missing DLLs
    - File system manipulation

95. **KnownDLLs Bypass** - Bypass KnownDLLs protection
    - Path manipulation

---

### **Day 20: Code Caves & Patching**
96. **Code Cave Finder** - Find code caves in executables
    - PE parsing, section analysis

97. **Code Cave Injector** - Inject code into caves
    - APIs: `VirtualProtect`, `WriteProcessMemory`

98. **Entry Point Patcher** - Modify PE entry point
    - PE patching

99. **Import Table Patcher** - Modify imports
    - PE patching

100. **Export Table Patcher** - Modify exports
    - PE patching

---

### **Day 21: Anti-Analysis**
101. **Debugger Detector** - Detect debuggers
    - APIs: `IsDebuggerPresent`, `CheckRemoteDebuggerPresent`, PEB flags

102. **VM Detector** - Detect virtual machines
    - APIs: Registry checks, CPUID, timing

103. **Sandbox Detector** - Detect sandboxes
    - Sleep acceleration, user interaction checks

104. **Timing Check** - Anti-debugging timing
    - APIs: `GetTickCount`, `QueryPerformanceCounter`

105. **PEB Checker** - Check PEB flags for debugging
    - Manual PEB parsing

---

## **WEEK 4: Network & Communication**

### **Day 22: Network Sockets**
106. **TCP Client** - Basic TCP client
    - APIs: `WSAStartup`, `socket`, `connect`, `send`, `recv`

107. **TCP Server** - Basic TCP server
    - APIs: `socket`, `bind`, `listen`, `accept`

108. **HTTP Request Sender** - Send HTTP requests
    - APIs: `InternetOpenA`, `InternetConnectA`, `HttpSendRequestA`

109. **HTTPS Beacon** - C2 beacon over HTTPS
    - WinHTTP or WinINet APIs

110. **DNS Query Tool** - Perform DNS queries
    - APIs: `DnsQuery_A`

---

### **Day 23: Named Pipes Communication**
111. **Named Pipe Server** - IPC via named pipes
    - APIs: `CreateNamedPipeA`, `ConnectNamedPipe`

112. **Named Pipe Client** - Connect and communicate
    - APIs: `CreateFileA`, `ReadFile`, `WriteFile`

113. **Impersonation via Pipes** - Client impersonation
    - APIs: `ImpersonateNamedPipeClient`

114. **Anonymous Pipe Creator** - Create anonymous pipes
    - APIs: `CreatePipe`

115. **Pipe Spam** - Abuse named pipes
    - Enumeration and connection

---

### **Day 24: RPC & DCOM**
116. **RPC Client** - Remote Procedure Call client
    - APIs: RPC runtime

117. **RPC Server** - RPC server
    - APIs: RPC runtime

118. **DCOM Object Creator** - Create DCOM objects
    - COM APIs

119. **DCOM Lateral Movement** - Execute via DCOM
    - COM APIs

120. **WMI Remote Executor** - Execute commands via WMI
    - WMI COM interfaces

---

### **Day 25: File Operations**
121. **File Enumerator** - List files recursively
    - APIs: `FindFirstFileA`, `FindNextFileA`

122. **Alternate Data Stream Creator** - NTFS ADS
    - APIs: `CreateFileA` with stream syntax

123. **ADS Reader** - Read alternate streams
    - APIs: `CreateFileA`, `ReadFile`

124. **File Attribute Modifier** - Change file attributes
    - APIs: `SetFileAttributesA`

125. **Timestamp Modifier** - Modify file timestamps
    - APIs: `SetFileTime`

---

## **WEEK 5: Advanced Techniques**

### **Day 26: Exception Handling**
126. **SEH Walker** - Walk exception handlers
    - Manual SEH chain parsing

127. **VEH Installer** - Install vectored exception handler
    - APIs: `AddVectoredExceptionHandler`

128. **VEH Unhooker** - Remove VEH hooks
    - Memory manipulation

129. **Exception Handler Hijacker** - Hijack SEH
    - Stack manipulation

130. **Unhandled Exception Filter** - Set filter
    - APIs: `SetUnhandledExceptionFilter`

---

### **Day 27: Hardware Breakpoints**
131. **Hardware BP Setter** - Set hardware breakpoints
    - APIs: `GetThreadContext`, `SetThreadContext` (DR registers)

132. **Hardware BP Detector** - Detect hardware breakpoints
    - Context checking

133. **DR Register Manipulator** - Manipulate debug registers
    - Thread context manipulation

134. **Single Step Debugger** - Single-step execution
    - Trap flag manipulation

135. **INT3 Patcher** - Software breakpoints
    - Memory patching (0xCC)

---

### **Day 28: Thread Local Storage**
136. **TLS Callback Creator** - Add TLS callbacks
    - PE modification

137. **TLS Callback Executor** - Execute via TLS
    - PE structure manipulation

138. **TLS Index Reader** - Read TLS data
    - TEB parsing

139. **Fiber Creator** - Create fibers
    - APIs: `CreateFiber`, `SwitchToFiber`

140. **FLS Manipulator** - Fiber Local Storage
    - APIs: `FlsAlloc`, `FlsSetValue`

---

### **Day 29: Callback Manipulation**
141. **Callback Table Walker** - Walk callback tables
    - Manual PEB parsing

142. **Windows Hook Installer** - SetWindowsHookEx
    - APIs: `SetWindowsHookExA`

143. **Global Hook Creator** - System-wide hooks
    - APIs: `SetWindowsHookExA` with NULL thread

144. **Message Hook** - Hook window messages
    - APIs: Hook procedures

145. **CBT Hook** - Computer-Based Training hooks
    - APIs: `SetWindowsHookExA` with WH_CBT

---

### **Day 30: Atom Bombing & Advanced**
146. **Atom Table Manipulator** - Global atom tables
    - APIs: `GlobalAddAtomA`, `GlobalGetAtomNameA`

147. **Atom Bomber** - Atom bombing injection
    - NtQueueApcThread with atom tables

148. **Extra Window Memory** - EWMI technique
    - APIs: `SetWindowLongPtrA`

149. **PROPagate Injector** - Window properties
    - APIs: `SetPropA`, `EnumPropsA`

150. **Shatter Attack** - Window messaging attack
    - APIs: `SendMessageA` with WM_COPYDATA

---

## **BONUS: Shellcode & Obfuscation**

### **Week 6: Shellcode Development**
151. **Simple Shellcode Writer** - Write basic shellcode
152. **Position Independent Shellcode** - PIC shellcode
153. **Shellcode Encoder** - XOR encoder
154. **Shellcode Crypter** - Encrypt shellcode
155. **Polymorphic Engine** - Self-modifying code
156. **Metamorphic Engine** - Code transformation
157. **ROP Chain Builder** - Return-Oriented Programming
158. **JOP Chain Builder** - Jump-Oriented Programming
159. **Syscall Shellcode** - Direct syscall shellcode
160. **Staged Payload** - Multi-stage shellcode

---

## **Your Learning Strategy:**

1. **Build 2-3 programs per day**
2. **Test each one thoroughly**
3. **Combine techniques as you go**
4. **By Week 5, you'll know 160+ techniques**

---

**Start with Day 1, Program 1 today.** Build the Process Enumerator and show me the output! 🔥

This list will take you from zero to hero in Windows malware development. Every real technique used by APTs and red teams is covered here.
