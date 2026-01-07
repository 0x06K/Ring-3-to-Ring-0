Perfect—here’s the **backend call chain**, clean and surgical. This is how **`CreateProcessA` actually happens in Windows**, all the way into the kernel. No fluff.

---

## 🔁 High-level flow (user → kernel → user)

![Image](https://miro.medium.com/v2/resize%3Afit%3A1400/1%2AKQxvgdpMPtLGBOAHrMl13A.jpeg)

![Image](https://learn.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/images/userandkernelmode01.png)

![Image](https://captmeelo.com/static/img/2022-05-10-ntcreateuserprocess/process-flow.png)

### 1️⃣ `CreateProcessA` (user mode, Win32)

* ANSI wrapper
* Converts strings → Unicode
* Calls `CreateProcessW`

---

### 2️⃣ `CreateProcessW` (user mode)

* Validates parameters
* Builds process parameters (cmdline, env, cwd)
* Calls **`CreateProcessInternalW`**

---

### 3️⃣ `CreateProcessInternalW` (user mode, heavy lifting)

This is where real prep happens:

* Parses PE headers
* Resolves image path
* Sets flags (suspended, debug, etc.)
* Builds **RTL_USER_PROCESS_PARAMETERS**
* Prepares attributes

➡️ Then it calls **`NtCreateUserProcess`**

---

### 4️⃣ `NtCreateUserProcess` (SYSTEM CALL 🔥)

This is the **user → kernel boundary**.

CPU switches:

* Ring 3 → Ring 0
* You’re now in the kernel

From here on, **you have zero control**.

---

### 5️⃣ Kernel process creation (ntoskrnl)

Inside the kernel, Windows does:

* Create **EPROCESS** object
* Create **ETHREAD** (initial thread)
* Create **virtual address space**
* Create **page tables**
* Map the EXE image
* Set up PEB + initial stack
* Attach security token
* Register with scheduler

This is the *actual* process.

---

### 6️⃣ Return to user mode

* Kernel returns handles (process + thread)
* Thread may be **suspended** or **running**
* Loader finishes DLL loading
* Entry point executes

Process is alive.

---

## 🧠 Key kernel objects created

* **EPROCESS** → kernel process object
* **ETHREAD** → kernel thread object
* **Address space** → page tables
* **Section object** → mapped EXE
* **Handle table**

---

## 🔥 Critical realization (this matters)

> **User mode does NOT create processes.**
> It only **requests** them.

Only the kernel can:

* Create address spaces
* Create page tables
* Create EPROCESS
* Register threads with scheduler

That’s why kernel malware exists.

---

## One-line backend summary 💥

> **CreateProcessA → Win32 wrappers → system call → kernel builds EPROCESS + memory + thread → scheduler runs it.**
