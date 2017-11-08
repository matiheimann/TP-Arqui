/* sampleCodeModule.c */
<<<<<<< HEAD
#include <stdlib.h>
#include <plotter.h>
=======

void divideByCero();
>>>>>>> 6fb3caa82664f67fbab56562ac7afcdb82d8a01e

int main() {
	char exit = 0;

	while(!exit){

		putchar('>');

		char command[100] = {0};
		cuadratic(3.0,0.0,0.0);
		scanf(command);

		if(strcmp(command, "exit")==0)
			exit = 1;

		else if(startsWith(command, "echo ")) {
			printf(command+5);
			putchar('\n');
		}

		else if(strcmp(command, "clear")==0) {
			clear();
		}

		else if(strcmp(command, "divide by cero")==0) {
			divideByCero();
		}

		else if(strcmp(command, "help")==0) {
			printf("Los comandos disponibles son: \n");
			printf("(a completar...)");
			putchar('\n');
		}

		else {
			printf("Invalid command, use help to see available commands");
			putchar('\n');
		}
	}

	clear();
	return 0;
}

void divideByCero() {
	int a = 1/0;
}