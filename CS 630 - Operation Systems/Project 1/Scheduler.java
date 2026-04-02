/*
* Arnav Kucheriya (ak2945)
* CS 630 - Operating Systems - Project 1
* 
* This program simulates a simple process scheduler with three programs (PA, PB, PC) that have different priorities and behaviors. 
* It creates processes, manages a ready queue based on priority, handles signals at specific time intervals, 
* and produces a Gantt chart of process execution along with the total signals received by each process.
*
* PROBLEM STATEMENT:
* Assume that P subscript A, P subscript B and P subscript C are three distinguished programs. 
* Assume that processes executing P subscript A have a priority of 2, processes executing P subscript B have a priority of 3 and processes executing P subscript C have a priority of 1. 
* In order to complete their execution, P subscript A needs 10 ticks, P subscript B needs 7 ticks and P subscript C needs 5 ticks. 
* Assume that processes running P subscript A and P subscript B will fork a new process every 3 ticks of execution. 
* The process running P subscript A forks new processes which execute P subscript B while the process running P subscript B forks new processes which execute P subscript C. 
* Assume that 2 processes P subscript 1 and P subscript 2 have arrived at t=0. P subscript 1 and P subscript 2 are going to execute programs P subscript A and P subscript B respectively. 
8 Furthermore, there is some hardware failure in this computer system that generates periodic signals and sends them to the currently running process every 3 ticks. 
* The first signal arrives at time t=3. Implement this scenario illustrating the scheduling of these processes if a priority with a round-robin scheduling algorithm is used. 
* Assume that a time quantum of 4 is used. Also assume that a smaller priority number means a higher priority.
*
* Your program is expected to:
*   A. Display the correct Gantt Chart showing appropriate time intervals. (35 points)
*   B. Display the total number of signals received by each individual process. (15 points)
*/

public class Scheduler {

    // -------------------------------------------------------------------------
    // Program IDs
    // -------------------------------------------------------------------------
    static final int PA = 0, PB = 1, PC = 2;

    // Priority: lower number = higher priority. PA=2, PB=3, PC=1
    static final int[]    PRI  = {2, 3, 1};
    // Total ticks each program needs to finish
    static final int[]    NEED = {10, 7, 5};

    // -------------------------------------------------------------------------
    // Process table (parallel arrays, max 300 processes)
    // -------------------------------------------------------------------------
    static final int MAX = 300;
    static int[]    prog  = new int[MAX];     // program this process runs
    static int[]    rem   = new int[MAX];     // remaining ticks
    static int[]    exec  = new int[MAX];     // ticks executed so far
    static int[]    sigs  = new int[MAX];     // signals received
    static String[] name  = new String[MAX];  // process name e.g. "P1"
    static boolean[]done  = new boolean[MAX];
    static int      np    = 0;                // number of processes created
    static int      pctr  = 0;                // counter for naming (P1, P2, ...)

    // -------------------------------------------------------------------------
    // Ready queue: simple array, sorted by priority (ascending), FIFO within
    // -------------------------------------------------------------------------
    static int[] rq   = new int[MAX];
    static int   rqsz = 0;

    static void enq(int id) {
        int p   = PRI[prog[id]];
        int ins = rqsz;
        // Find insertion point: before first entry with lower priority (higher number)
        for (int i = 0; i < rqsz; i++) {
            if (PRI[prog[rq[i]]] > p) { ins = i; break; }
        }
        // Shift right to make room
        for (int i = rqsz; i > ins; i--) rq[i] = rq[i-1];
        rq[ins] = id;
        rqsz++;
    }

    static int deq() {
        int id = rq[0];
        for (int i = 0; i < rqsz-1; i++) rq[i] = rq[i+1];
        rqsz--;
        return id;
    }

    // -------------------------------------------------------------------------
    // Gantt chart: store every quantum slice separately (do NOT merge)
    // -------------------------------------------------------------------------
    static int[] gid = new int[10000];   // process index
    static int[] gst = new int[10000];   // start time
    static int[] gen = new int[10000];   // end time
    static int   gn  = 0;

    static void addSlice(int id, int s, int e) {
        if (s == e) return;
        gid[gn] = id;
        gst[gn] = s;
        gen[gn] = e;
        gn++;
    }

    // -------------------------------------------------------------------------
    // Create a process and place it on the ready queue
    // -------------------------------------------------------------------------
    static int mkProc(int program) {
        pctr++;
        int id   = np++;
        prog[id] = program;
        rem[id]  = NEED[program];
        exec[id] = 0;
        sigs[id] = 0;
        name[id] = "P" + pctr;
        done[id] = false;
        enq(id);
        return id;
    }

    // -------------------------------------------------------------------------
    // Main simulation
    // -------------------------------------------------------------------------
    public static void main(String[] args) {

        mkProc(PA);   // P1 runs PA
        mkProc(PB);   // P2 runs PB

        int time    = 0;
        int nextSig = 3;   // signals at t=3, 6, 9, 12, ...

        while (rqsz > 0) {

            int cur      = deq();
            int quantum  = 4;
            int sliceSt  = time;

            // ------ tick loop ------------------------------------------------
            while (quantum > 0 && rem[cur] > 0) {

                // Signal check at the START of this tick.
                // Per the problem note: a signal at the boundary between two
                // processes goes to the newly executing one. This is naturally
                // satisfied because we check at the very first tick of each
                // newly dispatched slice (right after dequeue).
                if (time == nextSig) {
                    sigs[cur]++;
                    nextSig += 3;
                }

                // Execute one tick
                exec[cur]++;
                rem[cur]--;
                time++;
                quantum--;

                // Fork check
                // PA forks a new PB every 3 ticks of its execution
                // PB forks a new PC every 3 ticks of its execution
                if ((prog[cur] == PA || prog[cur] == PB) && exec[cur] % 3 == 0) {
                    int childProg = (prog[cur] == PA) ? PB : PC;
                    mkProc(childProg);

                    // If child has strictly higher priority, preempt current process
                    if (PRI[childProg] < PRI[prog[cur]]) {
                        addSlice(cur, sliceSt, time);
                        sliceSt = time;
                        if (rem[cur] > 0) enq(cur);
                        cur     = deq();
                        quantum = 4;
                    }
                }

                // Completion check
                if (rem[cur] == 0) {
                    done[cur] = true;
                    break;
                }
            }

            addSlice(cur, sliceSt, time);
            if (!done[cur]) enq(cur);
        }

        // =====================================================================
        // OUTPUT A: Gantt Chart  (format: [start - end] : Pname)
        // =====================================================================
        System.out.println("--- GANTT CHART ---");
        for (int i = 0; i < gn; i++) {
            System.out.println("[" + gst[i] + " - " + gen[i] + "] : " + name[gid[i]]);
        }

        // =====================================================================
        // OUTPUT B: Total signals received per process
        // =====================================================================
        System.out.println("\n--- SIGNALS RECEIVED ---");
        for (int i = 0; i < np; i++) {
            System.out.println(name[i] + " received " + sigs[i] + " signal(s)");
        }
    }
}