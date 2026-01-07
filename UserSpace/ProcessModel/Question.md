I’m gonna be blunt (in a good way):
**implementing that whole list is NOT the right first path**. That list is an **index of techniques**, not a learning order.

From a *real* maldev / defender-research POV, you don’t learn by grinding techniques — you learn by **mastering primitives**.

---

## 🧠 The correct maldev learning model (battlefield-first)

Think of malware like chess, not Pokémon.
You don’t “collect injections”, you **reuse the same 5–6 core mechanics** everywhere.

---

## 🔥 The ONLY things malware actually does in a process

Every item on your list reduces to **these primitives**:

1. **Get a process**
2. **Get memory**
3. **Write to memory**
4. **Change memory permissions**
5. **Get execution**
6. **Blend with normal behavior**

That’s it.
Everything else is just *branding*.

![Image](https://www.r-tec.net/files/content/img/News%2BEvents/Blog_Process-Injection-Avoiding-Kernel-Triggered-Memory-Scans/Figure%202%3A%20Suspicious%20combination%20for%20Process%20Injection.png)

![Image](https://miro.medium.com/v2/resize%3Afit%3A1400/1%2AfCsubQV50V0eu8AlEFLzVQ.png)

![Image](https://media.licdn.com/dms/image/v2/D4D12AQFWM24b1vHQtA/article-cover_image-shrink_720_1280/B4DZdEXlbUHkAI-/0/1749198723304?e=2147483647\&t=nmmZ0_2P4P4VhE_Tw6S_Q2KEA5jlqWQ7pSMlxzS2Fqo\&v=beta)

---

## 🚫 Why your list is dangerous (learning-wise)

If you start “implementing technique #1 to #50”:

* You’ll cargo-cult PoCs
* You’ll memorize APIs, not understand why
* You’ll break on any modern EDR
* You’ll panic when Windows changes

That’s how people get stuck at *script-kiddie-with-C* level.

---

## ✅ The RIGHT path (student → real maldev brain)

### **Phase 1 — Process & memory mastery (mandatory)**

Before *any* injection technique, you must explain **without notes**:

* Image vs Private Data vs Mapped File
* Why RW→RX matters
* Where threads start execution
* What PEB/TEB are used for
* Why page tables isolate processes

If you can’t explain these, injection is meaningless.

---

### **Phase 2 — ONE classic technique (not 15)**

Pick **ONE** of these (doesn’t matter which):

* Classic DLL Injection
* Process Hollowing
* Remote Thread Creation

Learn it to answer:

* Why does it work?
* What kernel objects are touched?
* What memory regions change?
* What would EDR flag?

🎯 Goal: **understand the mechanism**, not the trick.

---

### **Phase 3 — Execution methods (THIS is the real game)**

Execution is harder than allocation.

Master **execution vectors**, conceptually:

* Thread creation
* APC delivery
* Callback-based execution
* Existing thread hijack

Once you understand *execution*, half your list collapses into duplicates.

---

### **Phase 4 — Memory abuse, not injection**

This is where real maldev lives:

* Page permissions
* Copy-on-write
* Shared sections
* Heap behavior
* Stack behavior

At this point:

> **Injection techniques become interchangeable tools.**

---

### **Phase 5 — Defense-aware thinking**

You don’t ask:

> “Can I inject?”

You ask:

> “What does this look like to telemetry?”

That’s when you stop being a learner and start being dangerous (in the academic sense).

---

## 🔍 Your list, reclassified (truth table)

* **Classic Injection** → learning exercises
* **Advanced Injection** → variants of timing + execution
* **Memory Techniques** → the *actual core skill*

So the right order is:

> **Memory → Execution → Process → Technique**

NOT:

> ❌ Technique → Technique → Technique

---

## One-line truth bomb 💣

> **Injection techniques are symptoms; memory control is the disease.**

