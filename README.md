### MalDevJournal
This is my personal collection of malware development notes, tools, code snippets, and resources I explore and learn from. It’s my go-to place to keep everything organized and handy.

# FROM THE SHADOWS TO SOURCE
**2026 Goal: Project Shadow Walk**

# MalDevJournal - Techniques Database
---

## **🔥 USER-MODE INJECTION & EXECUTION**

### Classic Injection (1-15)
1. Classic DLL Injection
2. Reflective DLL Injection
3. Process Hollowing
4. Thread Execution Hijacking
5. Remote Thread Creation
6. QueueUserAPC Injection
7. APC Injection
8. DLL Sideloading
9. NtCreateThreadEx Injection
10. RtlCreateUserThread Injection
11. PE Injection
12. Memory Module Loading
13. Manual PE Mapping
14. Module Stomping
15. DLL Hollowing

### Advanced Injection (16-35)
16. Process Ghosting
17. Process Doppelgänging
18. Process Herpaderping
19. Process Reimaging
20. Transacted Hollowing
21. Early Bird Injection
22. Early Cascade Injection
23. Atom Bombing
24. Fiber Local Storage (FLS) Abuse
25. Extra Window Memory Injection (EWMI)
26. PROPagate Injection
27. SetWindowLong Injection
28. Window Subclassing Injection
29. SetWindowsHookEx Injection
30. Thread Pool Injection (Pool Party)
31. Special User APC (NtQueueApcThreadEx)
32. APC-Based Process Hollowing
33. NtTestAlert Injection
34. Cross-Session APC Injection
35. Code Cave Injection

### Memory Techniques (36-50)
36. VAD Manipulation
37. Memory Mapped Files Abuse
38. Section Object Hooking
39. Shared Memory Injection
40. File Mapping Injection
41. Memory Section Manipulation
42. Heap Spraying
43. Stack Pivoting
44. Copy-on-Write (CoW) Exploitation
45. TEB Manipulation
46. PEB Manipulation
47. Callback Overwriting
48. Stack Patching
49. Remote Memory Allocation
50. Memory Page Permission Modification

---

## **🔥 HOOKING TECHNIQUES**

51. IAT (Import Address Table) Hooking
52. EAT (Export Address Table) Hooking
53. Inline Hooking (Function Trampolines)
54. Hot Patching
55. Detours/Function Interception
56. Exception Directory Hooking
57. Return Address Overwriting
58. VTable Hooking
59. PLT/GOT Hooking
60. Entry Point Patching
61. TLS Callback Hooking
62. Vectored Exception Handler Chaining

---

## **🔥 EDR/AV EVASION**

### Unhooking & Bypass (63-75)
63. ETW Unhooking
64. AMSI Unhooking
65. AMSI Bypass via Memory Patching
66. ETW Provider Disabling
67. Direct Syscalls
68. Indirect Syscalls
69. Syscall Stomping
70. Heaven's Gate (WOW64 Bypass)
71. Thread Stack Spoofing
72. Syscall Number Extraction
73. API Set Schema Resolution
74. Fresh ntdll.dll Mapping
75. Self-Debugging Hook Manipulation

### Anti-Analysis (76-90)
76. Control Flow Flattening
77. Opaque Predicates
78. Instruction Substitution
79. Code Virtualization
80. Packing & Crypting
81. Multi-Layer Packing
82. Anti-Debugging (IsDebuggerPresent)
83. Anti-Debugging (PEB Flags)
84. Anti-Debugging (Timing Checks)
85. Anti-VM Detection
86. Anti-Sandbox Detection
87. Anti-Emulation Techniques
88. API Hashing
89. String Encryption
90. Dynamic API Resolution

---

## **🔥 PROCESS MANIPULATION**

91. Token Theft & Impersonation
92. Token Duplication
93. Parent PID Spoofing
94. Process Parameters Spoofing
95. Command Line Argument Spoofing
96. Environment Variable Injection
97. Process Mitigation Policy Bypass
98. Process Access Token Manipulation
99. Self-Deleting Payloads
100. TLS Callback Injection
101. Thread Context Manipulation
102. Fiber Execution
103. Critical Section Manipulation

---

## **🔥 SHELLCODE TECHNIQUES**

104. Position-Independent Shellcode
105. Self-Modifying Shellcode
106. Polymorphic Shellcode
107. Metamorphic Shellcode
108. Encoded Shellcode (XOR, Base64)
109. Staged Shellcode Delivery
110. Shellcode via Clipboard
111. Shellcode via Environment Variables
112. Fileless Shellcode Execution
113. Return-Oriented Programming (ROP)
114. Jump-Oriented Programming (JOP)
115. Call-Oriented Programming (COP)
116. Data-Oriented Programming (DOP)
117. Sigreturn-Oriented Programming (SROP)

---

## **🔥 PERSISTENCE TECHNIQUES**

### Registry & Services (118-130)
118. Registry Run Key Persistence
119. Service Creation & Modification
120. Service DLL Hijacking
121. DLL Proxy/Forwarding
122. DLL Search Order Hijacking
123. AppInit_DLLs Injection
124. AppCert DLLs Injection
125. Image File Execution Options (IFEO) Hijacking
126. Silent Process Exit Monitoring
127. Accessibility Features Replacement
128. Screensaver Replacement
129. Logon Scripts Modification
130. Shell Extensions Registration

### COM & WMI (131-140)
131. COM Hijacking
132. DCOM Lateral Movement
133. WMI Event Subscription
134. WMI Event Consumer Persistence
135. Scheduled Task Injection
136. Scheduled Task Modification
137. Application Shimming
138. SDB (Shim Database) Injection
139. Browser Helper Object (BHO)
140. Context Menu Handlers

### Advanced Persistence (141-155)
141. Property Sheet Handlers
142. Icon Handlers
143. Thumbnail Handlers
144. Preview Handlers
145. Print Processor Hijacking
146. Network Provider DLL
147. Security Support Provider (SSP)
148. Authentication Package Registration
149. Password Filter DLL
150. Credential Provider Hijacking
151. Office Add-in Persistence
152. IIS Module Installation
153. NTFS Alternate Data Streams (ADS)
154. NTFS Extended Attributes
155. BITS Jobs Abuse

---

## **🔥 APPLICATION EXPLOITS**

156. Office Macro Execution
157. Excel 4.0 (XLM) Macros
158. Office Template Injection
159. VBA Stomping
160. PowerShell AMSI Bypass
161. PowerShell Reflection-Based Injection
162. PowerShell Runspace Injection
163. .NET Assembly Loading
164. .NET Assembly Hollowing
165. CLR Hosting
166. AppDomain Manager Injection
167. SQL Server CLR Assemblies
168. Browser Extension Injection
169. Electron App Injection
170. Node.js Require Hijacking
171. Python Import Hijacking
172. Java ClassLoader Manipulation

---

## **🔥 PRIVILEGE ESCALATION**

### Hardware-Based (173-180)
173. Hardware Breakpoints (DR0-DR7)
174. Vectored Exception Handling (VEH)
175. Structured Exception Handler (SEH) Overwrite
176. SEHOP Bypass
177. Control Flow Guard (CFG) Bypass
178. Shadow Stack Bypass (CET)
179. Return Flow Guard (RFG) Bypass
180. Arbitrary Code Guard (ACG) Bypass

### Token & Credential (181-190)
181. Named Pipe Impersonation
182. Named Pipe Client Impersonation
183. Kerberos Ticket Injection (Pass-the-Ticket)
184. NTLM Hash Pass-the-Hash
185. Window Station Manipulation
186. Desktop Object Manipulation
187. Job Object Manipulation
188. Mailslot Abuse
189. Kerberoasting
190. NTLM Hash Relay

---

## **🔥 COMMUNICATION & C2**

191. Named Pipes Communication
192. Mailslots Communication
193. Shared Memory Communication
194. Window Messages (WM_COPYDATA)
195. Clipboard Monitoring
196. DNS Tunneling
197. ICMP Tunneling
198. HTTP/HTTPS C2
199. WebSocket C2
200. SMB Named Pipes
201. RPC Communication
202. DCOM Communication
203. WMI Communication
204. Registry as Communication Channel
205. File System as Communication Channel

---

## **🔥 KERNEL & ROOTKIT TECHNIQUES**

206. SSDT Hooking
207. DSE Bypass (Driver Signature Enforcement)
208. BYOVD (Bring Your Own Vulnerable Driver)
209. PatchGuard Bypass
210. Kernel Callback Tampering
211. IDT Hooking
212. MSR Manipulation
213. Kernel Object Hooking
214. DKOM (Direct Kernel Object Manipulation)
215. Kernel APC Injection
216. Process Token Swapping
217. PsSetCreateProcessNotifyRoutine Hijacking
218. NtQuerySystemInformation Abuse

---

## **🔥 BOOTKIT & FIRMWARE**

219. UEFI Bootkit
220. Bootloader Infection
221. SMM Rootkits
222. Intel ME Backdoors
223. PXE Boot Hijacking
224. UEFI Variable Tampering
225. EFI System Partition Malware
226. BIOS Bootkits
227. TPM Chip Exploits
228. Secure Boot Bypass
229. PCI Option ROM Attacks
230. ACPI Table Manipulation
231. Hibernation File Injection
232. BCD Manipulation
233. MBR Infection
234. VBR Injection

---

## **🔥 HARDWARE & SIDE-CHANNEL**

235. Rowhammer Exploits
236. Spectre & Meltdown
237. PLATYPUS Attack
238. Transient Execution Attacks (LVI, MDS, RIDL, Zombieload)
239. JTAG Exploitation
240. HDD Firmware Rootkits
241. PCIe DMA Injection
242. Power Analysis Attacks
243. USB Rubber Ducky Payloads
244. BadUSB Firmware Injection
245. Cold Boot Attacks
246. EMFI (Electromagnetic Fault Injection)
247. CPU Cache Timing Attacks
248. GPU Memory Stealing

---

## **🔥 NETWORK ATTACKS**

249. ARP Cache Poisoning
250. DNS Spoofing
251. TCP Session Hijacking
252. SMB Relay Attack
253. LLMNR/NBT-NS Poisoning
254. RDP Hijacking
255. DHCP Starvation
256. VLAN Hopping
257. Rogue Access Point
258. SSRF Exploits
259. Man-in-the-Middle (MITM)
260. DNS Cache Poisoning

---

**Total: 260 Pure Techniques**

*No fluff. No basics. Just weaponizable knowledge.* 🔥


✅ **Teaches you system internals** – You’ll understand memory, processes, and privilege escalation.  
✅ **Gives you initial access** – No point in writing malware if you can’t breach the system first.  
✅ **Builds a hacker mindset** – You’ll learn how attackers think and bypass security mechanisms.  
✅ **Bridges into malware dev** – Once you know exploits, writing stealthy malware is **10x easier**.  

---
 

👀 **if your goal is to write persistent malware immediately**, you **can** start with maldev **and learn exploitation later**. **Just know that your malware will be basic at first.**  

