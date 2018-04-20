#include <stdio.h>
#include "memoryManager.h"

int main(int argc, char const *argv[])
{
	initializeMemory();
	alloc(10);
	alloc(5000);
	alloc(10);
	alloc(5000);
}