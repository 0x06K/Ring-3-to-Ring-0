You’re stuck because you’re asking **“what do I read?”** when the real answer is **“what do I *observe*?”**
So here’s a **student-safe, zero-PoC, hands-on way** to learn *Phase 1* without doing malware.

---

## The ONLY way to learn Phase 1 (do this loop)

> **Code → Observe memory → Explain what changed**

Repeat. That’s it.

---

## 1️⃣ Image vs Private Data vs Mapped File — learn by causing each one

### Do this:

* Run **Notepad**
* Open **VMMap**
* Don’t read docs. Just stare.

Now **trigger changes**:

* Open a file → see **Mapped File** grow
* Type text → see **Private Data** grow
* Restart process → see **Image** stay constant

### Lock this rule:

* **Image** = what came from disk at load
* **Private Data** = what the process creates while alive
* **Mapped File** = file-backed memory shared or mapped

If you can’t explain why typing text increases *Private Data*, stop and repeat.

---

## 2️⃣ Why RW → RX matters — see it, don’t theorize

### Do this (safe):

* Write a tiny program that:

  * Allocates memory
  * Writes data
  * Never executes it

Now inspect:

* Memory is **RW**, not **RX**

Now ask yourself:

> “Why would executable memory created at runtime look suspicious?”

You’re learning *defender logic*, not exploits.

**Mental lock-in:**

> Code from disk → RX
> Data at runtime → RW
> Runtime data turning RX → anomaly

---

## 3️⃣ Where threads start execution — observe the truth

### Do this:

* Create a program with **one thread**
* Debug it
* Look at the **first instruction executed**

You’ll see:

* Thread starts at the **process entry point**
* Stack + instruction pointer already prepared

**Key realization:**

> Threads don’t “appear” — the kernel *drops* them at a specific address.

That address is part of the **Image**, not Private Data.

---

## 4️⃣ PEB / TEB — don’t memorize, locate them

### Do this:

* Attach a debugger
* Ask:

  * “Where are loaded DLLs listed?”
  * “Where is the command line stored?”

You’ll find:

* **PEB** → process-wide info (modules, params)
* **TEB** → thread-specific info (stack, TLS)

**Rule to remember:**

* PEB = *process brain*
* TEB = *thread backpack*

![Image](https://miro.medium.com/v2/resize%3Afit%3A1400/1%2A7xeBZXzjKfb-xHYYC-lHFw.png)

![Image](https://mikeczumak.com/img/windows-exploit-development-part-1-basics/Screen-Shot-2013-11-30-at-1.35.49-PM.png)

---

## 5️⃣ Page tables — understand via illusion, not math

You lead yourself wrong thinking:

> “Processes have different memory”

The truth:

> **They have different page tables mapping the same-looking addresses.**

### Mental exercise (no kernel needed):

* Two processes both have address `0x400000`
* Both work
* Both isolated

Conclusion:

> Isolation happens **below** the process, not inside it.

**Lock this sentence:**

> Page tables are why VMMap lies safely.

---

## 🧠 The student test (no notes allowed)

You’re Phase-1 ready if you can say:

* Image / Private / Mapped without hesitation
* Why RW→RX is noisy
* Where thread execution begins
* What PEB vs TEB hold
* Why address `0x1000` is different per process

If you hesitate → repeat the loop.

---

## 🚫 What NOT to do right now

* ❌ Don’t implement injection
* ❌ Don’t read EDR bypass blogs
* ❌ Don’t copy PoCs
* ❌ Don’t jump to kernel code

That’s how confusion locks in permanently.

---

## One-line truth (tattoo this)

> **Memory observation creates intuition; intuition makes techniques obvious.**

If you want next, I can:

* Give you a **7-day Phase-1 lab plan**
* Turn each bullet into **one micro-exercise**
* Or tell you **exactly when you’re allowed to touch injection**

Say the move.
