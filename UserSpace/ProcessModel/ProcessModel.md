Alright—**maldev POV, but *conceptual*, not “how-to crime”**. Think **threat modeling**, not a cookbook. 😈➡️🧠

---

## 🧠 Malware’s mental model of a process

From maldev eyes, a **process = attack surface + camouflage**.

> **Everything valuable happens in memory. Disk is optional.**

![Image](https://www.researchgate.net/publication/220673411/figure/fig1/AS%3A671523727753228%401537115141459/PE-File-and-Memory-Layout-Differences.jpg)

![Image](https://d38b7da4edvzl5.cloudfront.net/secarma/wp-content/uploads/2021/04/Picture1.png)

![Image](https://learn.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/images/virtualaddressspace01.png)

---

## What each region means to malware (high-level)

### 🧬 Image (EXE/DLLs)

* **What it is:** File-backed code mapped at load.
* **Maldev take:** Predictable, monitored, signatures everywhere.
* **Use:** Blend in (living-off-the-land), hijack legit modules.
* **Risk:** High detection.

---

### 🧠 Private Data (the gold mine)

* **What it is:** Anonymous, process-only memory.
* **Maldev take:** Best place to *exist*.
* **Why:** Not on disk, not shared, created at runtime.
* **Signals defenders watch:** RW→RX transitions, weird alloc patterns.

---

### 🧵 Stacks (per-thread)

* **What it is:** Call frames, return addresses.
* **Maldev take:** Temporary control or data staging.
* **Risk:** Fragile; crashes = instant spotlight.

---

### 🧰 Heaps (native / managed)

* **What it is:** Dynamic allocations.
* **Maldev take:** Persistence for in-memory state.
* **Managed heap:** GC can move stuff → instability.
* **Defender clue:** Heap spray patterns.

---

### 🗂️ Mapped Files

* **What it is:** File-backed shared memory.
* **Maldev take:** Covert sharing / IPC.
* **Tradeoff:** Leaves a disk footprint (defenders can trace).

---

## The *real* maldev priorities (conceptual)

1. **Stealth:** Minimize disk artifacts; memory-only presence.
2. **Stability:** Don’t crash the host process.
3. **Control:** Get execution without screaming.
4. **Persistence (in-memory):** Survive while the process lives.
5. **Evasion:** Look like normal allocations & threads.

---

## What defenders actually hunt (FYI)

* Unusual **memory permissions**
* Suspicious **thread creation**
* Abnormal **allocation lifetimes**
* Memory regions **not tied to images**
* Cross-process **handle abuse**

If you understand *why* these stand out, you understand the game.

---

## Clean takeaway

> **Malware doesn’t “run programs” — it manipulates memory semantics inside processes.**
> **Processes are battlegrounds; memory regions are terrain.**

# Refrences
- https://medium.com/@amitmoshel70/mysteries-of-the-windows-kernel-pt-1-processes-objects-d677a5afcd9b