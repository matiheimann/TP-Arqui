/* sampleCodeModule.c */
#include <stdlib.h>
#include "shlib.h"

int main() {
	char end = 0;
	printWelcomeMessage();

	while(!end){
		putchar('>');
		ps();
		char command[100] = {0};
		scanf(command);
		end = execute(command);
	}
	clear();
	exit();
	return 0;
}