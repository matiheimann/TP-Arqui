/* sampleCodeModule.c */
#include "messageHolderTesting.h"
#include "mutexTesting.h"
#include "shlib.h"
#include <stdlib.h>

void main()
{
	char end = 0;
	printWelcomeMessage();
	while (!end) {
		putchar('>');
		char command[100] = {0};
		scanf(command);
		end = execute(command);
	}

	exitProcess();
}
