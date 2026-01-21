#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>


int main(int argc, char *argv[])
{
	int i, fd, result;
	long filesize;
	unsigned int  *map;
	unsigned int ivalue;
        unsigned long long total = 0;
	int numints;

	if(argc!=3 || sscanf(argv[1], "%d", &numints)!=1){
		printf("%s count pathname\n", argv[0]);
		exit(1);
	}

	filesize=numints * sizeof(unsigned int);

	fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
	if (fd == -1) {
		perror("Error opening file for writing");
		exit(EXIT_FAILURE);
	}

	result = lseek(fd, filesize-1, SEEK_SET);
	if (result == -1) {
		close(fd);
		perror("Error calling lseek() to 'stretch' the file");
		exit(EXIT_FAILURE);
	}

	result = write(fd, "", 1);
	if (result != 1) {
		close(fd);
		perror("Error writing last byte of the file");
		exit(EXIT_FAILURE);
	}

	map = mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		close(fd);
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}

	srand48((unsigned)time(NULL));  
	for (i = 0; i <numints; ++i) {
		ivalue = lrand48()%1000;
		printf("%d\n", ivalue);
		map[i] = ivalue;
		total += ivalue;
	}

	if (munmap(map, filesize) == -1) 
		perror("Error un-mmapping the file");

	close(fd);
	printf("Total: %llu\n", total);
	return 0;
}
