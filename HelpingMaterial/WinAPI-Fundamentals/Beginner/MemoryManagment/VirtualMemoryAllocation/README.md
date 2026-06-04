
## **VIRTUAL MEMORY ALLOCATION**

### Basic Allocation
- `VirtualAlloc` - Allocate in current process
- `VirtualAllocEx` - Allocate in remote process
- `VirtualFree` - Free in current process
- `VirtualFreeEx` - Free in remote process

### Enhanced Allocation (Windows 10+)
- `VirtualAlloc2` - Extended parameters (NUMA nodes, memory partition)
- `VirtualAlloc2FromApp` - UWP version
- `VirtualAllocFromApp` - UWP version of VirtualAlloc

### Native API Variants
- `NtAllocateVirtualMemory` - Native allocation (more control)
- `NtFreeVirtualMemory` - Native free

### NUMA-Aware Allocation
- `VirtualAllocExNuma` - Allocate on specific NUMA node