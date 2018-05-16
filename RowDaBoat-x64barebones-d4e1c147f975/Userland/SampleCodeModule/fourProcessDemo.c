#include "fourProcessDemo.h"
#include <stdlib.h>

void fourProcessesDemo(int argc, char** argv)
{
	int i;
	for (i = 0; i < 4; i++) {
		newProcess((void *)&processDemo, 0, NULL);
	}
	ps();
	exitProcess();
}
void processDemo(int argc, char** argv)
{
  int pid = getPid();
  printf("\n-----Hi from process ");
  printInt(pid);
  printf("-----\n");
  exitProcess();
}
