# WinIo64 Privilege Escalation PoC

## Overview

This proof-of-concept demonstrates a **complete privilege escalation chain** exploiting the WinIo64.sys driver vulnerability (catalogued in LOLDrivers UUID: 96501e5b-e4f2-41a9-a8ee-d09e36d31a39). The exploit leverages unvalidated physical memory read/write access to steal the System process token and achieve kernel-level privilege elevation.


**Critical flaw:** No validation on address ranges, I/O ports, or caller privileges. Any unprivileged user can read/write arbitrary kernel memory.

## Exploit Chain

There is no validation check at all neither on address mapping nor on I/O port operations which results in arbitrary physical memory read/write from unprivileged usermode. On mapping the physical address range, I was able to find the System EPROCESS structure with pattern scanning (1–2 minutes). I read the flink pointer at offset 0x448 (ActiveProcessLinks), translated it to physical via page table walk, traversed the linked list, found my own EPROCESS, and replaced my token with the System token at offset 0x4B8, achieving instant privilege escalation to SYSTEM.

<img width="1911" height="1010" alt="image" src="https://github.com/user-attachments/assets/df5e9778-67d3-4f88-8ac4-d81e07ffba8b" />




### Requirements
- Windows 10
- Visual Studio
- WinIo64.sys driver loaded on target system

### Build
```bash
# With MSVC
cl.exe /O2 /W4 poc.c /link ntdll.lib

```

### Execution
```bash
# Load driver first (requires admin or existing SYSTEM context via other means)
sc.exe create WinIo64 binPath=C:\windows\temp\WinIo64.sys type=kernel
sc.exe start WinIo64

# Run exploit
poc.exe

# Verify SYSTEM shell
whoami
# Output: NT AUTHORITY\SYSTEM
```



## Disclaimer

**This PoC was developed as a practice exercise on a publicly documented vulnerable driver. It is tested on Windows10 (10.0.19045 N/A Build 19045).**  The vulnerability and exploitation techniques are already public knowledge. This code is provided for **educational and authorized security testing purposes only** in controlled lab environments.

**Unauthorized access to computer systems is illegal.** Use this PoC only on systems you own or have explicit written permission to test.

## References

- **LOLDrivers Database:** https://www.loldrivers.io/drivers/96501e5b-e4f2-41a9-a8ee-d09e36d31a39/
- **KDU (Kernel Driver Utility):** https://github.com/hfiref0x/KDU
- **Windows x64 Page Tables:** https://en.wikipedia.org/wiki/X86-64#Virtual_address_space_details
- **EPROCESS Structure:** Windows kernel internals documentation
