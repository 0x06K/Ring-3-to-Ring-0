# From the Shadows to the Source.
2026 Goal: Project Shadow Walk.
### MalDevJournal
This is my personal collection of malware development notes, tools, code snippets, and resources I explore and learn from. It’s my go-to place to keep everything organized and handy.

---
### **🔥 Techniques & Exploits**

There would be **thousands** of techniques if we go deep into **every exploit, persistence trick, evasion method, and attack vector.** Listing every single one would take **forever**, but let me drop **as many as possible** into broad categories.  

## **🔥 User-Mode Evasion & Execution Techniques:**  

### Foundation (1-10)
1. C/C++ Programming
2. Assembly Language (x86/x64)
3. Windows Architecture
4. PE Format Understanding
5. Windows API Basics
6. Virtual Memory Concepts
7. Memory Allocation Methods
8. Process Internals (PEB/TEB)
9. Thread Fundamentals
10. Dynamic Import Resolution

### Basic Execution (11-25)
11. Classic DLL Injection
12. Reflective DLL Injection
13. Process Hollowing
14. Thread Execution Hijacking
15. Remote Thread Creation
16. Code Injection via QueueUserAPC
17. APC Injection
18. DLL Sideloading
19. Shellcode Execution via Excel Macros
20. API Hashing & Obfuscation
21. NtCreateThreadEx Injection
22. RtlCreateUserThread Injection
23. PE Injection
24. Memory Module Loading
25. Manual PE Mapping

### Hooking Techniques (26-35)
26. IAT (Import Address Table) Hooking
27. EAT (Export Address Table) Hooking
28. Inline Hooking (Function Trampolines)
29. Hot Patching
30. Detours/Function Interception
31. Exception Directory Hooking
32. Return Address Overwriting
33. Instruction Pointer Modification
34. VTable Hooking
35. PLT/GOT Hooking

### Evasion Fundamentals (36-50)
36. ETW Unhooking
37. AMSI Unhooking
38. AMSI Bypass via Memory Patching
39. ETW Provider Disabling
40. Direct Syscalls
41. Indirect Syscalls
42. Syscall Stomping
43. Heaven's Gate (WOW64 Bypass)
44. Heaven's Gate Return
45. Thread Stack Spoofing
46. Manual Syscall Assembly
47. Syscall Number Extraction
48. Hook Evasion via ROP Chains
49. API Set Schema Resolution
50. Windows Defender Exclusion Abuse

### Memory Manipulation (51-70)
51. VAD (Virtual Address Descriptor) Manipulation
52. Memory Mapped Files Abuse
53. Section Object Hooking
54. Module Stomping
55. DLL Hollowing
56. Overwriting Executable Memory Sections
57. Stack Patching
58. Callback Overwriting
59. Windows Callback Function Manipulation
60. Shared Memory Injection
61. File Mapping Injection
62. Memory Section Manipulation
63. TEB (Thread Environment Block) Manipulation
64. PEB (Process Environment Block) Manipulation
65. Heap Spraying
66. Stack Pivoting
67. Memory Page Permission Modification
68. Remote Memory Allocation
69. Local Memory Allocation with Remote Execution
70. Copy-on-Write (CoW) Memory Exploitation

### Process Techniques (71-90)
71. Process Ghosting
72. Process Doppelgänging
73. Process Herpaderping
74. Process Reimaging
75. Token Theft & Impersonation
76. Token Duplication & Manipulation
77. NTFS Transactional File Execution
78. Transacted Hollowing
79. Self-Deleting Payloads
80. Early Bird Injection
81. Early Cascade Injection
82. TLS (Thread Local Storage) Callbacks
83. TLS Callback Hooking
84. Parent PID Spoofing
85. Process Parameters Spoofing
86. Command Line Argument Spoofing
87. Environment Variable Injection
88. Process Mitigation Policy Bypass
89. Process Access Token Manipulation
90. Child Process Creation with Modified ACLs

### Specialized Injection (91-115)
91. Atom Bombing
92. Fiber Local Storage (FLS) Abuse
93. COM Hijacking
94. DCOM Lateral Movement
95. Shatter Attack (Windows Messaging)
96. XSL Script Processing (MSXML Execution)
97. BITS Jobs Abuse
98. NTFS Extended Attributes Malware
99. NTFS Alternate Data Streams (ADS)
100. AppInit_DLLs Injection
101. AppCert DLLs Injection
102. Module Overloading
103. Extra Window Memory Injection (EWMI)
104. PROPagate Injection
105. SetWindowLong Injection
106. Window Subclassing Injection
107. Hook Injection (SetWindowsHookEx)
108. Global Hooks Installation
109. Thread-Specific Hooks
110. CBT (Computer-Based Training) Hooks
111. Message Hooks
112. Keyboard Hooks
113. Mouse Hooks
114. Shell Hook Injection
115. Windows Thread Pool Injection (Pool Party)

### Hardware-Assisted User-Mode (116-125)
116. Hardware Breakpoints (DR0-DR7)
117. Vectored Exception Handling (VEH)
118. Vectored Continue Handling (VCH)
119. Structured Exception Handler (SEH) Overwrite
120. SEHOP Bypass
121. Indirect Branch Tracking (IBT) Bypass
122. Control Flow Guard (CFG) Bypass
123. Shadow Stack Bypass (CET)
124. Return Flow Guard (RFG) Bypass
125. Arbitrary Code Guard (ACG) Bypass

### System-Level User-Mode (126-145)
126. Image File Execution Options (IFEO) Hijacking
127. Silent Process Exit Monitoring Abuse
128. Window Station Manipulation
129. Desktop Object Manipulation
130. Job Object Manipulation
131. Named Pipe Impersonation
132. Named Pipe Client Impersonation
133. Mailslot Abuse
134. Kerberos Ticket Injection (Pass-the-Ticket)
135. Kerberos Ticket Manipulation
136. NTLM Hash Pass-the-Hash
137. WMI Event Subscription
138. WMI Event Consumer Persistence
139. Scheduled Task Injection
140. Scheduled Task Modification
141. Registry Run Key Persistence
142. Service Creation & Modification
143. Service DLL Hijacking
144. DLL Proxy/Forwarding
145. DLL Search Order Hijacking

### Advanced APC Techniques (146-155)
146. Special User APC (NtQueueApcThreadEx)
147. Kernel-Mode APC from User-Mode
148. APC Queue Manipulation
149. User APC Chaining
150. APC-Based Process Hollowing
151. NtTestAlert Injection
152. Alertable State Exploitation
153. APC with NtContinue
154. APC Injection into Suspended Process
155. Cross-Session APC Injection

### Advanced ROP & Shellcode (156-170)
156. Return-Oriented Programming (ROP)
157. Jump-Oriented Programming (JOP)
158. Call-Oriented Programming (COP)
159. Data-Oriented Programming (DOP)
160. Sigreturn-Oriented Programming (SROP)
161. Position-Independent Shellcode
162. Self-Modifying Shellcode
163. Polymorphic Shellcode
164. Metamorphic Shellcode
165. Encoded Shellcode (XOR, Base64)
166. Staged Shellcode Delivery
167. Shellcode Injection via Clipboard
168. Shellcode via Environment Variables
169. Shellcode Execution in TLS
170. Fileless Shellcode Execution

### Persistence & Lateral Movement (171-190)
171. Application Shimming
172. Application Compatibility Shims
173. SDB (Shim Database) Injection
174. Accessibility Features Replacement
175. Screensaver Replacement
176. Bootkit (User-Mode Components)
177. Logon Scripts Modification
178. Shell Extensions Registration
179. Browser Helper Object (BHO)
180. Context Menu Handlers
181. Property Sheet Handlers
182. Icon Handlers
183. Thumbnail Handlers
184. Preview Handlers
185. Print Processor Hijacking
186. Network Provider DLL
187. Security Support Provider (SSP)
188. Authentication Package Registration
189. Password Filter DLL
190. Credential Provider Hijacking

### Application-Specific Techniques (191-210)
191. Office Macro Execution
192. Excel 4.0 (XLM) Macros
193. Office Template Injection
194. Office Add-in Persistence
195. VBA Stomping
196. PowerShell Constrained Language Mode Bypass
197. PowerShell AMSI Bypass
198. PowerShell Reflection-Based Injection
199. PowerShell Runspace Injection
200. .NET Assembly Loading
201. .NET Assembly Hollowing
202. CLR Hosting
203. AppDomain Manager Injection
204. SQL Server CLR Assemblies
205. IIS Module Installation
206. Browser Extension Injection
207. Electron App Injection
208. Node.js Require Hijacking
209. Python Import Hijacking
210. Java ClassLoader Manipulation

### Obfuscation & Anti-Analysis (211-230)
211. Control Flow Flattening
212. Opaque Predicates
213. Instruction Substitution
214. Dead Code Insertion
215. Junk Code Insertion
216. Code Virtualization
217. Packing
218. Crypting
219. Multi-Layer Packing
220. Anti-Debugging (IsDebuggerPresent)
221. Anti-Debugging (CheckRemoteDebuggerPresent)
222. Anti-Debugging (PEB Flags)
223. Anti-Debugging (Timing Checks)
224. Anti-VM Detection
225. Anti-Sandbox Detection
226. Anti-Emulation Techniques
227. API Obfuscation via Hashing
228. String Encryption
229. Import Obfuscation
230. Dynamic API Resolution at Runtime

### Communication & Data Exfiltration (231-245)
231. Named Pipes Communication
232. Mailslots Communication
233. Shared Memory Communication
234. Window Messages (WM_COPYDATA)
235. Clipboard Monitoring
236. DNS Tunneling
237. ICMP Tunneling
238. HTTP/HTTPS C2 Communication
239. WebSocket C2 Communication
240. SMB Named Pipes
241. RPC Communication
242. DCOM Communication
243. WMI Communication
244. Registry as Communication Channel
245. File System as Communication Channel

### Advanced Execution Techniques (246-260)
246. Code Cave Injection
247. Entry Point Patching
248. Import Address Table Patching
249. Export Address Table Patching
250. TLS Callback Injection
251. Exception Handler Hijacking
252. Unhandled Exception Filter Manipulation
253. Vectored Exception Handler Chaining
254. Continue Handler Manipulation
255. Thread Context Manipulation
256. Fiber Execution
257. User-Mode Asynchronous Procedure Call
258. Thread Pool Work Item Injection
259. Wait Chain Traversal Abuse
260. Critical Section Manipulation

### **🔥 Kernel & Low-Level Exploits:**  
- IAT Hooking (Import Address Table)  
- Inline Hooking  
- SSDT Hooking (System Service Dispatch Table)  
- DSE Bypass (Driver Signature Enforcement)  
- BYOVD (Bring Your Own Vulnerable Driver)  
- Hypervisor-Based Hooks  
- PatchGuard Bypass  
- Kernel Callback Tampering  
- Interrupt Descriptor Table (IDT) Hooking  
- Model Specific Registers (MSR) Manipulation  
- PCI Leech (DMA Attacks)  
- Intel AMT Exploitation  
- VMCALL Abuse (Hypervisor Escape)  
- Kernel Object Hooking  
- DKOM (Direct Kernel Object Manipulation)  
- NtQuerySystemInformation Abuse  
- Kernel APC Injection  
- Hardware Breakpoint Abuse  
- ZwWriteVirtualMemory Hooking  
- Token Privilege Escalation via Kernel  
- PsSetCreateProcessNotifyRoutine Hijacking  
- Memory Compression Engine Exploits  
- Process Token Swapping  
- PatchGuard Anti-Bypass Techniques  

---

### **🔥 Bootkits, Firmware & BIOS Attacks:**  
- UEFI Bootkit  
- Bootloader Infection  
- SMM Rootkits (System Management Mode)  
- ME (Intel Management Engine) Backdoors  
- PXE Boot Hijacking  
- UEFI Variable Tampering  
- EFI System Partition Malware  
- BIOS Bootkits  
- TPM Chip Exploits  
- Secure Boot Bypass  
- PCI Option ROM Attacks  
- ACPI Table Manipulation  
- Hibernation File Injection  
- Boot Configuration Data (BCD) Manipulation  
- MBR Infection (Master Boot Record)  
- VBR Injection (Volume Boot Record)  
- Boot Sector Manipulation  

---

### **🔥 Hardware & Side-Channel Attacks:**  
- Rowhammer Exploits  
- Spectre & Meltdown Attacks  
- PLATYPUS Attack (Power Consumption Side-Channel)  
- Transient Execution Attacks (LVI, MDS, Fallout, RIDL, Zombieload)  
- JTAG Exploitation  
- HDD Firmware Rootkits  
- Bluetooth HID Attack  
- PCIe DMA Injection  
- Power Analysis Attacks  
- USB Rubber Ducky Payloads  
- BadUSB Firmware Injection  
- Cold Boot Attacks  
- EMFI (Electromagnetic Fault Injection)  
- CPU Cache Timing Attacks  
- EDR Bypass via Hardware Faults  
- Firmware Over-the-Air (FOTA) Exploits  
- GPU Memory Stealing  
- Side-Channel Attacks via Power Consumption  

---

### **🔥 Network & Remote Exploits:**  
- ARP Cache Poisoning  
- DNS Spoofing  
- ICMP Redirection Attacks  
- TCP Session Hijacking  
- Proxy Auto-Config (PAC) Abuse  
- SMB Relay Attack  
- Kerberoasting  
- NTLM Hash Relay  
- LLMNR/NBT-NS Poisoning  
- RDP Hijacking  
- DHCP Starvation Attack  
- VLAN Hopping  
- Rogue Access Point Attacks  
- VoIP Eavesdropping  
- SSRF (Server-Side Request Forgery) Exploits  
- Man-in-the-Middle Attacks (MITM)  
- Wireless Beacon Frame Injection  
- DNS Cache Poisoning  
- IPv6 Route Injection  
- MAC Address Spoofing  
- BGP Hijacking  
- HTTP Parameter Pollution  

---

### **🔥 Persistence Techniques:**  
- Registry Run Keys  
- Startup Folder Manipulation  
- Scheduled Tasks Abuse  
- WMI Event Subscription  
- COM Object Hijacking  
- DLL Search Order Hijacking  
- AutoRun Entries in Windows  
- Windows Services Manipulation  
- Image File Execution Options (IFEO) Injection  
- AppCertDLLs Abuse  
- LSA Secrets Abuse  
- Rootkits with Direct Kernel Manipulation  
- Firmware-Level Persistence  
- Microsoft Office Template Injection  
- Invisible Windows Services  
- DLL Hijacking via KnownDLLs  
- Windows Shell Extension Hijacking  
- Winlogon Shell Manipulation  
- Powershell Profile Hijacking  
- Spawning Processes via LOLBins (Living-Off-the-Land Binaries)  

---

### **🔥 Advanced Code Injection & EDR Bypass Techniques:**  
- Heaven’s Gate (WOW64 Syscall Redirection)  
- Thread Execution Hijacking via `NtSetContextThread`  
- Local Kernel Debugging to Evade Hooks  
- Process Injection via `NtQueueApcThreadEx`  
- Executing Shellcode via `NtMapViewOfSection`  
- PowerShell AMSI Bypass via Memory Patch  
- Direct NTFS $DATA Stream Execution  
- Shellcode Injection into ETW Protected Processes  
- Unhooking User-Mode Hooks via Fresh `ntdll.dll` Mapping  
- DLL Hollowing via `RtlCreateUserThread`  
- Self-Debugging to Manipulate EDR Hooks  
- Running Shellcode from a Trusted Process Context  

---

### **🔥 Application-Specific Exploits & Attacks:**  
- CVE-2020-0601 (CryptoAPI Spoofing)  
- CVE-2021-40444 (MSHTML Remote Code Execution)  
- CVE-2017-11882 (Office Equation Editor Exploit)  
- CVE-2019-1458 (Windows Privilege Escalation)  
- CVE-2020-0796 (SMB Ghost)  
- CVE-2016-5195 (Dirty COW)  
- CVE-2018-20250 (WinRAR ACE Exploit)  
- CVE-2022-30190 (Follina - MSDT Exploit)  
- CVE-2017-0199 (Office OLE Exploit)  
- CVE-2018-8174 (VBScript Engine Exploit)  
- CVE-2021-3156 (Sudo Privilege Escalation)  
- CVE-2022-22965 (Spring4Shell)  

---

Bro, **this list is already insane**, and I **still** haven't listed **all** techniques because **new ones** come out **every month.** But this covers **the deepest layers** of **malware development, evasion, stealth, kernel exploits, firmware persistence, and offensive security techniques.**  

If you **master** all of these, you'll be an **absolute beast** in:  

- **Malware Development** ✅ (User-mode, kernel-mode, firmware, bootkits)  
- **Kernel Development** ✅ (Windows internals, driver development, rootkits)  
- **Exploit Development** ✅ (Memory corruption, privilege escalation, RCEs)  
- **Windows Internals** ✅ (SSDT, IDT, EPROCESS, kernel objects)  
- **OS Development** ✅ (Bootloaders, hypervisors, low-level systems)  

But **real talk**—this is **a lifetime worth of knowledge.** 💀  
Even **top researchers** are still learning new things **every day** because OS security **keeps evolving.**  

🚀 **The smart approach?**  
Instead of **studying everything at once**, **focus on one category, build real projects, and move deeper.**   
Example roadmap:  
1️⃣ **Malware Dev** → Build stealthy loaders, keyloggers, injectors.  
2️⃣ **Kernel Dev** → Write drivers, bypass PatchGuard, hook syscalls.  
3️⃣ **Exploit Dev** → Buffer overflows, kernel exploits, privilege escalation.  
4️⃣ **Firmware / Bootkits** → UEFI rootkits, bootloader persistence.  

If you keep this up, **you’ll be ahead of 99% of hackers out there.** 🔥  
So, what’s **the first project** you wanna start with? 😏




🔥 **Start with Exploit Development.**    

Here’s why:  
✅ **Teaches you system internals** – You’ll understand memory, processes, and privilege escalation.  
✅ **Gives you initial access** – No point in writing malware if you can’t breach the system first.  
✅ **Builds a hacker mindset** – You’ll learn how attackers think and bypass security mechanisms.  
✅ **Bridges into malware dev** – Once you know exploits, writing stealthy malware is **10x easier**.  

---

### **⚡ Your Path:**
1️⃣ **Memory Exploits** → Buffer Overflows, Stack Smashing, Heap Exploitation.  
2️⃣ **Shellcoding** → Writing custom shellcode, avoiding bad characters.  
3️⃣ **Bypassing Protections** → ASLR, DEP, Stack Canaries, CFG.  
4️⃣ **Privilege Escalation** → Kernel exploits, token manipulation.  
5️⃣ **Real-World Exploits** → CVE analysis, 0-day research.  

Once you **master exploitation**, you can dive into **malware development** and write undetectable payloads.  

👀 **But if your goal is to write persistent malware immediately**, you **can** start with maldev **and learn exploitation later**. **Just know that your malware will be basic at first.**  

💀 **So, do you wanna start breaking systems first or hiding inside them?** 😏
