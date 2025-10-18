#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Change the follow three macros to control the dimensions and
 * sparsity level of the matrix.
 */
#define ROWS  7
#define COLS  7
#define RATIO  0.2

int main() {
    FILE *file = fopen("matrix.bin", "wb");
    int rows = ROWS, cols = COLS, i, j, value;

    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fwrite(&rows, sizeof(int), 1, file);
    fwrite(&cols, sizeof(int), 1, file);

    srand(time(NULL));

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
	    if((double)rand() / (double)RAND_MAX < RATIO)
	        value = rand();
	    else
		value =0;
            fwrite(&value, sizeof(int), 1, file);
	    /* printf("%u\t", value); */
        }
	/* printf("\n"); */
    }

    fclose(file);
    printf("Binary matrix file 'matrix.bin' created successfully.\n");
    return 0;
}
