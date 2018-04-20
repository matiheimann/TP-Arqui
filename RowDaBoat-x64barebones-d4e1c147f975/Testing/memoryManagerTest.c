#include <stdio.h>
#include "memoryManager.h"

int main(int argc, char const *argv[])
{
	printf("lalala\n");

	char memory[MEMORY_SIZE];
	initializeMemory(memory);

	void * ptr1;
	void * ptr2;

	int i = 0;
	char * p[1024];

	while (i < 1024) {
		p[i] = (char *)allocate(sizeof(char)*2048);
		i++;
	}

	i = 0;
	
	while (i < 1024) {
		deallocate(p[i]);
		i++;
	}

	allocate(2048);

	return 1;

}