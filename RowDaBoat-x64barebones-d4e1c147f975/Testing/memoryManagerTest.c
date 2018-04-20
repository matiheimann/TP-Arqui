#include <stdio.h>
#include "memoryManager.h"

int main(int argc, char const *argv[])
{
	initializeMemory();

	void * ptr1;
	void * ptr2;

	int i = 0;
	char * p[3000];

	while (i < 3000) {
		p[i] = (char *)alloc(sizeof(char)*1);
		i++;
	}

	i = 0;
	
	while (i < 3000) {
		dealloc(p[i]);
		i++;
	}

	ptr1 = alloc(10);
	ptr2 = alloc(10);
	alloc(3000);
	dealloc(ptr1);
	dealloc(ptr2);
	alloc(5000);


	return 1;

}