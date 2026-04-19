/*
* Arnav Kucheriya (ak2945)
* CS 630 - Operating Systems - Project 2
*/

public class RRScheduler {

    // Process data
    static final int N = 7;
    static final String[] PNAME   = {"P1","P2","P3","P4","P5","P6","P7"};
    static final int[]    ARRIVAL = { 0,   5,  15,  35,  50,  65,  94};
    static final int[]    BURST   = {19,  16,  27,  13,  10,  26,  19};

    static int[]    rem           = new int[N];
    static int[]    resp          = new int[N];
    static int[]    finish        = new int[N];
    static int[]    blockedUntil  = new int[N];   // -1 = not blocked
    static boolean[]inReady       = new boolean[N];

    // I/O events: trigger times and their durations (hardcoded as parallel arrays)
    static final int[] IO_TIME = {18, 43, 72, 104};
    static final int[] IO_DUR  = {18, 22, 25,  14};
    static boolean[]   ioFired = new boolean[4];   // mark once fired

    // Ready queue (FIFO, max 200 entries)
    static final int QMAX = 200;
    static int[] rq   = new int[QMAX];
    static int   rqSz = 0;

    static void enq(int i) {
        if (!inReady[i] && rem[i] > 0 && blockedUntil[i] == -1) {
            rq[rqSz++] = i;
            inReady[i] = true;
        }
    }

    static int deq() {
        int id = rq[0];
        for (int k = 0; k < rqSz - 1; k++) rq[k] = rq[k+1];
        rqSz--;
        return id;
    }

    // Gantt chart storage
    static final int GMAX = 5000;
    static String[] gName  = new String[GMAX];
    static int[]    gStart = new int[GMAX];
    static int[]    gEnd   = new int[GMAX];
    static int      gN     = 0;

    static void addSlice(String nm, int s, int e) {
        if (s == e) return;
        gName[gN]  = nm;
        gStart[gN] = s;
        gEnd[gN]   = e;
        gN++;
    }

    // Main
    public static void main(String[] args) {

        // Initialize arrays
        for (int i = 0; i < N; i++) {
            rem[i]          = BURST[i];
            resp[i]         = -1;
            finish[i]       = -1;
            blockedUntil[i] = -1;
            inReady[i]      = false;
        }

        // Seed ready queue with t=0 arrivals
        for (int i = 0; i < N; i++)
            if (ARRIVAL[i] == 0) enq(i);

        int TQ      = 4;
        int cur     = -1;
        int qLeft   = 0;
        int sliceSt = 0;
        int time    = 0;
        int MAX_T   = 3000;

        while (time < MAX_T) {

            // 1. Unblock processes whose I/O has completed
            for (int i = 0; i < N; i++) {
                if (blockedUntil[i] == time) {
                    blockedUntil[i] = -1;
                    enq(i);
                }
            }

            // 2. Enqueue newly arrived processes
            for (int i = 0; i < N; i++)
                if (ARRIVAL[i] == time && rem[i] > 0) enq(i);

            // 3. Dispatch: needed if no current process, quantum expired, or process done
            boolean needDispatch = (cur == -1) || (rem[cur] == 0) || (qLeft == 0);

            if (needDispatch) {
                // Save current gantt slice
                if (cur != -1 && sliceSt < time)
                    addSlice(PNAME[cur], sliceSt, time);

                // Re-enqueue if quantum expired (not finished, not blocked)
                if (cur != -1 && rem[cur] > 0 && qLeft == 0 && blockedUntil[cur] == -1)
                    enq(cur);

                if (rqSz == 0) {
                    // CPU idle
                    cur = -1;
                    time++;
                    continue;
                }

                cur     = deq();
                qLeft   = TQ;
                sliceSt = time;
                if (resp[cur] == -1) resp[cur] = time - ARRIVAL[cur];
            }

            // 4. Check if an I/O event fires RIGHT NOW (before executing the tick).
            //    Per the note: if quantum expiry and I/O coincide, process → blocked.
            //    This is naturally handled: we dispatched above (giving the process
            //    a fresh quantum), and now we immediately block it before any tick runs.
            int ioDur = -1;
            for (int k = 0; k < IO_TIME.length; k++) {
                if (!ioFired[k] && IO_TIME[k] == time) {
                    ioDur      = IO_DUR[k];
                    ioFired[k] = true;
                    break;
                }
            }

            if (ioDur != -1) {
                // Block the running process
                if (sliceSt < time) addSlice(PNAME[cur], sliceSt, time);
                blockedUntil[cur] = time + ioDur;
                inReady[cur]      = false;
                cur   = -1;
                qLeft = 0;
                // Don't advance time — loop again to dispatch next process
                continue;
            }

            // 5. Execute one tick
            rem[cur]--;
            qLeft--;
            time++;

            // 6. Completion check
            if (rem[cur] == 0) {
                finish[cur] = time;
                addSlice(PNAME[cur], sliceSt, time);
                cur   = -1;
                qLeft = 0;
            }

            // 7. All done?
            boolean allDone = true;
            for (int i = 0; i < N; i++) if (finish[i] == -1) { allDone = false; break; }
            if (allDone) break;
        }

        // OUTPUT 1: Gantt Chart
        System.out.println("--- GANTT CHART ---");
        for (int i = 0; i < gN; i++)
            System.out.println("[" + gStart[i] + " - " + gEnd[i] + "] : " + gName[i]);

        // OUTPUT 2: Waiting Time
        System.out.println("\n--- WAITING TIME ---");
        for (int i = 0; i < N; i++) {
            int tat = finish[i] - ARRIVAL[i];
            int wt  = tat - BURST[i];
            System.out.println(PNAME[i] + " : " + wt);
        }

        // OUTPUT 3: Response Time
        System.out.println("\n--- RESPONSE TIME ---");
        for (int i = 0; i < N; i++)
            System.out.println(PNAME[i] + " : " + resp[i]);

        // OUTPUT 4: Turn-Around Time
        System.out.println("\n--- TURN-AROUND TIME ---");
        for (int i = 0; i < N; i++) {
            int tat = finish[i] - ARRIVAL[i];
            System.out.println(PNAME[i] + " : " + tat);
        }
    }
}