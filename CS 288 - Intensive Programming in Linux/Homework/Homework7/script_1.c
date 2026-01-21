#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

struct state {
    int tiles[N][N];
    int f, g, h;
    short zero_row, zero_column;   /* location (row and column) of blank tile 0 */
    struct state *next;
    struct state *parent;          /* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct state *start,*goal;
struct state *fringe = NULL, *closed = NULL;
struct state *succ_states[4];

void print_a_state(struct state *pstate) {
    int i,j;
    for (i=0;i<N;i++) {
        for (j=0;j<N;j++)
            printf("%2d ", pstate->tiles[i][j]);
        printf("\n");
    }
    printf("\n");
}

void initialize(char **argv){
    int j,k,index, tile;

    start=(struct state *) malloc(sizeof(struct state));
    if(start == NULL){
        fprintf(stderr,"malloc failed\n");
        exit(1);
    }
    index = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) {
            tile = atoi(argv[index++]);
            start->tiles[j][k]=tile;
            if(tile==0) {
                start->zero_row=j;
                start->zero_column=k;
            }
        }
    start->f=0;
    start->g=0;
    start->h=0;
    start->next=NULL;
    start->parent=NULL;
    printf("initial state\n");
    print_a_state(start);

    goal=(struct state *) malloc(sizeof(struct state));
    if(goal == NULL){
        fprintf(stderr,"malloc failed\n");
        exit(1);
    }
    goal_rows[0]=3;
    goal_columns[0]=3;

    for(index=1; index<NxN; index++){
        j=(index-1)/N;
        k=(index-1)%N;
        goal_rows[index]=j;
        goal_columns[index]=k;
        goal->tiles[j][k]=index;
    }
    goal->tiles[N-1][N-1]=0;       /* empty tile=0 */
    goal->f=0;
    goal->g=0;
    goal->h=0;
    goal->next=NULL;
    goal->parent=NULL;
    printf("goal state\n");
    print_a_state(goal);
}

/* swap two tiles in a state (does NOT touch zero_row/zero_column) */
void swap(int row1,int column1,int row2,int column2, struct state * pstate){
    int tmp = pstate->tiles[row1][column1];
    pstate->tiles[row1][column1] = pstate->tiles[row2][column2];
    pstate->tiles[row2][column2] = tmp;
}

/* 0 goes down by a row */
void move_down(struct state * pstate){
    swap(pstate->zero_row, pstate->zero_column,
         pstate->zero_row+1, pstate->zero_column, pstate);
    pstate->zero_row++;
}

/* 0 goes right by a column */
void move_right(struct state * pstate){
    swap(pstate->zero_row, pstate->zero_column,
         pstate->zero_row, pstate->zero_column+1, pstate);
    pstate->zero_column++;
}

/* 0 goes up by a row */
void move_up(struct state * pstate){
    swap(pstate->zero_row, pstate->zero_column,
         pstate->zero_row-1, pstate->zero_column, pstate);
    pstate->zero_row--;
}

/* 0 goes left by a column */
void move_left(struct state * pstate){
    swap(pstate->zero_row, pstate->zero_column,
         pstate->zero_row, pstate->zero_column-1, pstate);
    pstate->zero_column--;
}

int states_same(struct state *a,struct state *b) {
    int flg=FALSE;
    if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
        flg=TRUE;
    return flg;
}

/* update the f,g,h function values for a state pointed to by succ_states[i] */
void update_fgh(int i) {
    int r,c,tile;
    int h = 0;
    struct state *pstate = succ_states[i];
    if(pstate == NULL) return;

    /* g: cost so far from the start (each move costs 1) */
    if (pstate->parent != NULL)
        pstate->g = pstate->parent->g + 1;
    else
        pstate->g = 0;

    /* Manhattan distance heuristic (ignore tile 0) */
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            tile = pstate->tiles[r][c];
            if(tile == 0) continue;
            h += abs(r - goal_rows[tile]) + abs(c - goal_columns[tile]);
        }
    }
    pstate->h = h;
    pstate->f = pstate->g + pstate->h;
}

/* Filtering:
 * check the state pointed by succ_states[i] to determine whether this state is repeating.
 * free the state if it is repeating.
 */
void filter(int i, struct state *pstate_list){
    struct state *pstate = succ_states[i];
    struct state *curr;
    if(pstate == NULL) return;

    curr = pstate_list;
    while(curr != NULL){
        if(states_same(pstate, curr)){
            /* repeated state – discard */
            free(pstate);
            succ_states[i] = NULL;
            return;
        }
        curr = curr->next;
    }
}

/* expand a state, and get its children states.
 * Children states are stored in succ_states[0..3]
 * Order: 0=up,1=down,2=left,3=right (arbitrary but consistent)
 */
void expand(struct state *selected) {
    int i;
    for(i=0;i<4;i++) succ_states[i] = NULL;

    /* move up (blank row > 0) */
    if(selected->zero_row > 0){
        struct state *child = (struct state *) malloc(sizeof(struct state));
        if(child == NULL){ perror("malloc"); exit(1); }
        memcpy(child, selected, sizeof(struct state));
        child->parent = selected;
        child->next = NULL;
        move_up(child);
        succ_states[0] = child;
    }

    /* move down (blank row < N-1) */
    if(selected->zero_row < N-1){
        struct state *child = (struct state *) malloc(sizeof(struct state));
        if(child == NULL){ perror("malloc"); exit(1); }
        memcpy(child, selected, sizeof(struct state));
        child->parent = selected;
        child->next = NULL;
        move_down(child);
        succ_states[1] = child;
    }

    /* move left (blank col > 0) */
    if(selected->zero_column > 0){
        struct state *child = (struct state *) malloc(sizeof(struct state));
        if(child == NULL){ perror("malloc"); exit(1); }
        memcpy(child, selected, sizeof(struct state));
        child->parent = selected;
        child->next = NULL;
        move_left(child);
        succ_states[2] = child;
    }

    /* move right (blank col < N-1) */
    if(selected->zero_column < N-1){
        struct state *child = (struct state *) malloc(sizeof(struct state));
        if(child == NULL){ perror("malloc"); exit(1); }
        memcpy(child, selected, sizeof(struct state));
        child->parent = selected;
        child->next = NULL;
        move_right(child);
        succ_states[3] = child;
    }
}

/* merge the remaining states pointed to by succ_states[] into fringe.
 * Insert states based on their f values --- keep f values sorted (ascending).
 */
void merge_to_fringe() {
    int i;
    for(i=0;i<4;i++){
        struct state *s = succ_states[i];
        struct state *prev, *curr;

        if(s == NULL) continue;

        /* insert s into fringe sorted by f */
        if(fringe == NULL || s->f < fringe->f){
            s->next = fringe;
            fringe = s;
        } else {
            prev = fringe;
            curr = fringe->next;
            while(curr != NULL && curr->f <= s->f){
                prev = curr;
                curr = curr->next;
            }
            s->next = curr;
            prev->next = s;
        }
        /* clear pointer from succ_states so we don't reuse it accidentally */
        succ_states[i] = NULL;
    }
}

int main(int argc,char **argv) {
    int iter;
    struct state *curr_state, *solution_path=NULL;
    int i, pathlen=0;

    if(argc != 17){
        fprintf(stderr,"Usage: %s index0 index1 ... index15\n", argv[0]);
        return 1;
    }

    initialize(argv);  /* init initial and goal states */
    fringe = start;

    iter=0;
    while (fringe!=NULL) {
        curr_state=fringe;
        fringe=fringe->next;  /* get the first state from fringe to expand */

        if(states_same(curr_state,goal)){ /* a solution is found */
            /* trace back and add the states on the path to a list */
            while(curr_state!=NULL){
                curr_state->next = solution_path;
                solution_path = curr_state;
                curr_state = curr_state->parent;
                pathlen++;
            }

            printf("Path (length=%d):\n", pathlen);
            curr_state = solution_path;
            while(curr_state != NULL){
                print_a_state(curr_state);
                curr_state = curr_state->next;
            }
            return 0;
        }

        expand(curr_state);       /* generate new states */

        for(i=0;i<4;i++){
            filter(i,fringe);  /* Check succ_states[i] against fringe */
            filter(i,closed);  /* Check succ_states[i] against closed */
            update_fgh(i);     /* evaluate the state if it is not repeating */
        }

        merge_to_fringe(); /* add new states to fringe */

        curr_state->next = closed;
        closed = curr_state;  /* curr_state has been checked/expanded, add it to closed */

        if(iter++ % 1000 == 0) printf("iter %d\n", iter);
    }

    /* If we exit the loop without finding a solution */
    printf("no solution\n");
    return 0;
}
