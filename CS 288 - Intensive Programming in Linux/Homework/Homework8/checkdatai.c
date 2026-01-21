#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/* #define PRINTVALUES */

int main(int argc, char *argv[])
{
	int i, fd, ascending=1;
	unsigned long long total = 0;
	unsigned int *map;  
	int numfloats, filesize;

	if(argc!=2) {
		printf("%s pathname\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("Error opening file for reading");
		exit(EXIT_FAILURE);
	}

	lseek(fd, 0, SEEK_END);
	filesize = lseek(fd, 0, SEEK_CUR) ;
	numfloats = filesize >> 2;

	map = mmap(0, filesize, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		close(fd);
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}

	total += map[0];
#ifdef PRINTVALUES
	printf("%dth value (%u)\n", 0, map[0]);
#endif
	for (i = 1; i < numfloats; i++) {
#ifdef PRINTVALUES
		printf("%dth value (%u)\n", i, map[i]);
#else
		if(map[i] < map[i-1]) {
			printf("%dth value (%u) < %dth value (%u)\n", i, map[i], i-1, map[i-1]);
			ascending = 0;
		}
#endif
		total += map[i];
	}

	if (munmap(map, filesize) == -1) {
		perror("Error un-mmapping the file");
	}
	close(fd);

	if(ascending)
		printf("The values have been sorted in ascending order.\n");
	printf("Total: %llu\n", total);
	return 0;
}

