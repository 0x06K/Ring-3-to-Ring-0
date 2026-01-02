Short answer? **For Day 3 (Thread Management)** — **yes, that’s basically the full universe**.
Long answer (because precision matters): **there are no secret extra thread APIs hiding in a cave**. What *does* exist are **edge-case, rarely used, or internal variants**. I’ll give you the **clean, final, scoped list** so your toolbox is complete and mentally indexed.

No memory APIs. No process APIs. **Threads only.**

---

# ✅ **FINAL – COMPLETE THREAD MANAGEMENT API SET (User-Mode)**

If it touches **thread lifecycle, execution, scheduling, or state**, it’s here.

---

## 🧵 1. Thread Creation

### Win32

* `CreateThread`
* `CreateRemoteThread`
* `CreateRemoteThreadEx`
* `_beginthreadex`

### Native (NTDLL)

* `NtCreateThread`
* `NtCreateThreadEx`
* `ZwCreateThreadEx`
* `RtlCreateUserThread`

➡️ **Nothing else exists in user-mode** for thread creation.

---

## ⏸️ 2. Suspend / Resume

* `SuspendThread`
* `ResumeThread`
* `NtSuspendThread`
* `NtResumeThread`

✔️ That’s it.

---

## 🎯 3. Thread Context (Registers, RIP/RSP, etc.)

* `GetThreadContext`
* `SetThreadContext`
* `NtGetContextThread`
* `NtSetContextThread`
* `Wow64GetThreadContext`
* `Wow64SetThreadContext`

✔️ No hidden extras.

---

## 🔍 4. Thread Enumeration

### Toolhelp

* `CreateToolhelp32Snapshot`
* `Thread32First`
* `Thread32Next`

### Native

* `NtQuerySystemInformation`

  * `SystemProcessInformation`

✔️ Enumeration is intentionally limited.

---

## 🧬 5. Thread Information & Introspection

### Win32

* `GetThreadInformation`
* `SetThreadInformation`
* `GetThreadId`
* `GetCurrentThread`
* `GetCurrentThreadId`
* `OpenThread`

### Native

* `NtQueryInformationThread`
* `NtSetInformationThread`

Common info classes:

* `ThreadBasicInformation`
* `ThreadTimes`
* `ThreadPriority`
* `ThreadBasePriority`
* `ThreadQuerySetWin32StartAddress`
* `ThreadHideFromDebugger`

✔️ This is the **full introspection surface**.

---

## ⚖️ 6. Thread Scheduling & Priority

* `SetThreadPriority`
* `GetThreadPriority`
* `SetThreadPriorityBoost`
* `SetThreadAffinityMask`
* `SetThreadIdealProcessor`
* `SetThreadIdealProcessorEx`
* `NtSetInformationThread`

✔️ Scheduler control ends here.

---

## 🧨 7. APC (Asynchronous Procedure Calls)

* `QueueUserAPC`
* `NtQueueApcThread`
* `NtQueueApcThreadEx`
* `NtTestAlert`
* `SleepEx`
* `WaitForSingleObjectEx`

✔️ APC delivery has **no other entry points**.

---

## 🧗 8. Stack Walking / Call Stack (Thread-Scoped)

* `StackWalk64`
* `CaptureStackBackTrace`
* `RtlWalkFrameChain`
* `RtlLookupFunctionEntry`

✔️ Stack inspection is intentionally constrained.

---

## 🧪 9. Fibers (Thread Alternative, Still Thread-Bound)

* `ConvertThreadToFiber`
* `ConvertThreadToFiberEx`
* `CreateFiber`
* `CreateFiberEx`
* `SwitchToFiber`
* `DeleteFiber`

✔️ Fibers are user-mode scheduling on top of threads — still Day 3 material.

---

## 🧼 10. Thread Cleanup & Exit

* `ExitThread`
* `TerminateThread`
* `NtTerminateThread`
* `CloseHandle`

✔️ Termination surface is tiny by design.

---

