/* sampleCodeModule.c */
#include <stdlib.h>
#include "shlib.h"

void main() {
	char end = 0;
	printWelcomeMessage();
	while(!end){
		putchar('>');
		char command[100] = {0};
		scanf(command);
		end = execute(command);
	}
	clear();
	exit();
}