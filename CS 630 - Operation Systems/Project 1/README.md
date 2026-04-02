# Process Scheduler Simulation
### Priority Round-Robin Scheduling with Forking and Signal Handling
**Language:** Java | **File:** `Scheduler.java`

---

## Problem Statement

Three distinguished programs — **P_A**, **P_B**, and **P_C** — are scheduled on a CPU using a **Priority Round-Robin** algorithm with a time quantum of **4 ticks**.

- Processes executing **P_A** have a priority of **2**
- Processes executing **P_B** have a priority of **3**
- Processes executing **P_C** have a priority of **1**
- A **smaller priority number means higher priority** (P_C > P_A > P_B)

Two initial processes arrive at **t = 0**:
- **P1** executes program P_A
- **P2** executes program P_B

A hardware failure generates **periodic signals** sent to the currently running process every 3 ticks, with the **first signal at t = 3**.

> **Note:** If a signal arrives at the exact boundary between the end of one process's quantum and the start of a new process's execution, the signal is received by the **newly executing process**.

---

## Requirements & Constraints

### Scheduling Rules
| Property | Value |
|---|---|
| Algorithm | Priority + Round-Robin |
| Time Quantum | 4 ticks |
| Priority Order | Lower number = higher priority |
| Initial Processes | P1 (P_A) and P2 (P_B) at t=0 |

### Execution Requirements
| Program | Priority | Ticks Needed |
|---|---|---|
| P_A | 2 | 10 |
| P_B | 3 | 7 |
| P_C | 1 | 5 |

### Forking Rules
- A process running **P_A** forks a new **P_B** process every **3 ticks** of its own execution
- A process running **P_B** forks a new **P_C** process every **3 ticks** of its own execution
- Processes running **P_C** do not fork
- If a newly forked child has higher priority than the currently running process, the current process is **immediately preempted**

### Signal Rules
- A signal is sent to the currently running process every **3 ticks**
- First signal fires at **t = 3**, then t = 6, 9, 12, ...
- If a signal coincides with the start of a new process's slice, the **new process** receives it

### Submission Constraints
- Language must be **C, C++, or Java** only (`.c`, `.cpp`, `.cc`, or `.java`)
- **No built-in library functions** permitted — all functions must be written from scratch (including sorting)
- Code must **compile and run without errors** — non-compiling code receives a grade of zero
- Deadline is **2 weeks** from assignment date — no late submissions accepted

---

## How to Compile and Run

### Option 1 — Online Compiler (Recommended)
1. Visit [https://onlinegdb.com](https://onlinegdb.com) or [https://replit.com](https://replit.com)
2. Select **Java** as the language
3. Paste the contents of `Scheduler.java`
4. Click **Run**

### Option 2 — Local Java (requires JDK)
```bash
javac Scheduler.java
java Scheduler
```

### Option 3 — VS Code
1. Install VS Code and the **Extension Pack for Java**
2. Open `Scheduler.java`
3. Click the **Run** button above the `main` method

---

## How the Simulation Works

1. **Initialization** — P1 (P_A) and P2 (P_B) are added to the ready queue at t=0
2. **Dispatch** — The highest-priority process is selected from the ready queue (FIFO among equal priorities)
3. **Execution** — The process runs tick by tick up to the quantum limit (4 ticks)
4. **Signal Check** — At the start of each tick, if `time == nextSignalTime`, the running process receives a signal
5. **Fork Check** — After each tick, if the process has run a multiple of 3 ticks total, it forks a child
6. **Preemption** — If a forked child has higher priority than the current process, the current process is immediately preempted and the child runs next
7. **Re-queue** — If a process exhausts its quantum without finishing, it goes back to the end of its priority group in the ready queue
8. **Termination** — Simulation ends when the ready queue is empty and all processes are done

---

## Expected Output Format

### A. Gantt Chart (35 points)
Each line shows one quantum slice in the format `[start - end] : ProcessName`

```
--- GANTT CHART ---
[0 - 4] : P1
[4 - 8] : P1
[8 - 10] : P1
[10 - 13] : P2
[13 - 17] : P6
[17 - 18] : P6
...
```

### B. Signals Received (15 points)
Each line shows the total number of signals received by each process.

```
--- SIGNALS RECEIVED ---
P1 received 3 signal(s)
P2 received 2 signal(s)
P3 received 3 signal(s)
...
```

---

## Actual Output
### Gantt Chart Output
```powershell
--- GANTT CHART ---
[0 - 4] : P1
[4 - 8] : P1
[8 - 10] : P1
[10 - 13] : P2
[13 - 17] : P6
[17 - 18] : P6
[18 - 21] : P3
[21 - 25] : P7
[25 - 26] : P7
[26 - 29] : P4
[29 - 33] : P8
[33 - 34] : P8
[34 - 37] : P5
[37 - 41] : P9
[41 - 42] : P9
[42 - 45] : P2
[45 - 49] : P10
[49 - 50] : P10
[50 - 53] : P3
[53 - 57] : P11
[57 - 58] : P11
[58 - 61] : P4
[61 - 65] : P12
[65 - 66] : P12
[66 - 69] : P5
[69 - 73] : P13
[73 - 74] : P13
[74 - 75] : P2
[75 - 76] : P3
[76 - 77] : P4
[77 - 78] : P5
```

### Signals Received Output
```powershell
--- SIGNALS RECEIVED ---
P1 received 3 signal(s)
P2 received 2 signal(s)
P3 received 3 signal(s)
P4 received 2 signal(s)
P5 received 2 signal(s)
P6 received 1 signal(s)
P7 received 2 signal(s)
P8 received 2 signal(s)
P9 received 1 signal(s)
P10 received 2 signal(s)
P11 received 2 signal(s)
P12 received 1 signal(s)
P13 received 2 signal(s)
```

---

## File Structure

```
project/
├── Scheduler.java      # Main simulation source file
└── README.md           # This documentation file
```

---

## Grading Breakdown

| Component | Points |
|---|---|
| Correct Gantt Chart (Part A) | 35 |
| Correct Signal Counts (Part B) | 15 |
| **Total** | **50** |

