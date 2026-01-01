Here is the **clean, minimal, user-mode ONLY list** for **thread enumeration & information** — no extras, no explanation.

---

## ✅ THREAD ENUMERATION & INFO — USER MODE ONLY

### **Toolhelp APIs**

* `CreateToolhelp32Snapshot`
* `Thread32First`
* `Thread32Next`

---

### **Thread Information APIs**

* `GetThreadId`
* `GetThreadTimes`
* `GetThreadPriority`
* `GetExitCodeThread`

---

### **Native (ntdll.dll) APIs**

* `NtQueryInformationThread`
* `NtQuerySystemInformation` *(SystemProcessInformation)*

---

### **WOW64 (32-bit → 64-bit)**

* `NtWow64QueryInformationThread`

---

### **Thread Context (read-only allowed)**

* `GetThreadContext`
* `Wow64GetThreadContext`

---