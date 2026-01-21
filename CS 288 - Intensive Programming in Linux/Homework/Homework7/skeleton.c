#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0


/*   THIS IS NOT A COMPLETE PROGRAM.    */


struct state {
	int tiles[N][N];
	int f, g, h;
	short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
	struct state *next;
	struct state *parent;			/* used to trace back the solution */
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
	int i,j,k,index, tile;

	start=(struct state *) malloc(sizeof(struct state));
	index = 1;
	for (j=0;j<N;j++)
		for (k=0;k<N;k++) {
			tile=atoi(argv[index++]);
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
	goal_rows[0]=3;
	goal_columns[0]=3;

	for(index=1; index<NxN; index++){
		j=(index-1)/N;
		k=(index-1)%N;
		goal_rows[index]=j;
		goal_columns[index]=k;
		goal->tiles[j][k]=index;
	}
	goal->tiles[N-1][N-1]=0;	      /* empty tile=0 */
	goal->f=0;
	goal->g=0;
	goal->h=0;
	goal->next=NULL;
	printf("goal state\n");
	print_a_state(goal);

}

/* merge the remaining states pointed by succ_states[] into fringe. 
 * Insert states based on their f values --- keep f values sorted. */
void merge_to_fringe() { 
}

/*swap two tiles in a state*/
void swap(int row1,int column1,int row2,int column2, struct state * pstate){
}

/*update the f,g,h function values for a state pointed by a pointer in succ_states */
void update_fgh(int i) {
	struct state *pstate = succ_states[i];
	...
}

/* 0 goes down by a row */
void move_down(struct state * pstate){
}

/* 0 goes right by a column */
void move_right(struct state * pstate){
}

/* 0 goes up by a row */
void move_up(struct state * pstate){
}

/* 0 goes left by a column */
void move_left(struct state * pstate){
}

/* expand a state, and get its children states. Children states pointed by the pointers in succ_states.
 */
void expand(struct state *selected) {
	...
	succ_states[..] = ...;
	...
}

int states_same(struct state *a,struct state *b) {
	int flg=FALSE;
	if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
		flg=TRUE;
	return flg;
}

/* Filtering:
 * check the state pointed by succ_states[i] to determine whether this state is repeating.
 * free the state if it is repeating. 
 */ 
void filter(int i, struct state *pstate_list){ 
	struct state *pstate = succ_states[i];
	...
}

int main(int argc,char **argv) {
	int iter,cnt;
	struct state *curr_state, *cp, *solution_path;
	int ret, i, pathlen=0, index[N-1];

	solution_path=NULL;
	initialize(argv);	/* init initial and goal states */
	fringe=start; 

	iter=0; 
	while (fringe!=NULL) {	
		curr_state=fringe;
		fringe=fringe->next;  /* get the first state from fringe to expand */
		

		/* SOME NOTES FOR DEBUGGING:  
		 * Fix segmentation faults first. If the program cannot produce correct results,
		 * select an initial layout close to the goal layout, and debug the program with it.
		 * gdb is recommended. You may also print data on the screen. But this is not as
		 * convenient as using gdb.
		 * 
		 * If your program does not crash, but the result is not correct, you can
		 * print the state pointed by curr_state for the list of states examined during the search
		 * 
		 */

		if(states_same(curr_state,goal)){ /* a solution is found */
			do{ /* trace back and add the states on the path to a list */
				curr_state->next=solution_path;
				solution_path=curr_state;
				curr_state=curr_state->parent;
				pathlen++;
			} while(curr_state!=NULL);
			printf("Path (lengh=%d):\n", pathlen); 
			curr_state=solution_path;
			... /* print out the states on the list */
			break;
		}
		expand(curr_state);       /* generate new states */


		for(i=0;i<4;i++){
			filter(i,fringe); /* Check succ_states[i] agaist fringe to see if it is repeatng */
			filter(i,closed); /* Check succ_states[i] agaist closed to see if it is repeatng */
			update_fgh(i); /* evaluate the state if it is not repeating */
		}


		merge_to_fringe(); /* add new states to fringe */

		curr_state->next=closed;
		closed=curr_state;	/* curr_state has been checked/expand, add it to closed */
		/* print out something so that you know your program is still making progress 
		 */
		if(iter++ %1000 == 0) printf("iter %d\n", iter);
	}
	return 0;
} /* end of main */
