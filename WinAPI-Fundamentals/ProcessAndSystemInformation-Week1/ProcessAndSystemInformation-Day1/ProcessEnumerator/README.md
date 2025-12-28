
### Day 1: Process Enumeration

* **CreateToolhelp32Snapshot**
* **Process32First**
* **Process32Next**
* **EnumProcesses**
* **NtQuerySystemInformation**
* **CsrGetProcessId**
* **NtConnectPort**

These are the APIs whose **primary purpose is to enumerate processes**, not to fetch module names or other process details.


Here’s a **refined table of Day 1 “Process Enumeration APIs only”**, categorized by method type:

| Method Type      | Enumeration APIs                                              | Notes                                                   |
| ---------------- | ------------------------------------------------------------- | ------------------------------------------------------- |
| **Snapshot**     | `CreateToolhelp32Snapshot`, `Process32First`, `Process32Next` | Snapshot handle + iteration over processes              |
| **PSAPI**        | `EnumProcesses`                                               | Returns array of PIDs                                   |
| **Native**       | `NtQuerySystemInformation`                                    | Kernel-level enumeration via `SystemProcessInformation` |
| **CSRSS / ALPC** | `CsrGetProcessId`, `NtConnectPort`                            | Direct query to process subsystem(will work on it later)                       |

✅ This table includes only APIs that participate in the **enumeration itself**, regardless of whether they return some basic process info.

If you want, I can also make a **super-minimal version showing only the ones that enumerate PIDs without any extra details**. Do you want me to do that?
