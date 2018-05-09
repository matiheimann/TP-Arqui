#include <stdlib.h>
#include "fourProcessDemo.h"


void fourProcessesDemo(void)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		newProcess((void*)&processDemo, 0, NULL);
	}
	ps();
	exitProcess();
}
void processDemo(void)
{
	int pid = getPid();
	printf("Hi from process...\n");
	printInt(pid);
	exitProcess();
}

