#include <graphPlotterApp.h>
#include <stdlib.h>

void graphPlotter()
{
	clear();
	printf("PLOTTER PROGRAM\n");
	printf("Welcome to the graph plotter program\n");
	printf(
	    "Write 'addplot' to plot or 'exit' to exit program and return to "
	    "shell\n");

	while (1) {
		char command[20] = {0};
		putchar('>');
		scanf(command);
		if (strcmp(command, "addplot") == 0) {
			clear();
			plotCuadratic();
		}

		else if (strcmp(command, "exit") == 0) {
			clear();
			return;
		}

		else {
			printf("Invalid command\n");
		}
	}
}

void plotCuadratic()
{
	double a, b, c;

	printf("A.X^2 + B.X + C ");
	putchar('\n');

	printf("A: ");
	char aParameter[20] = {0};
	scanf(aParameter);
	if (!parseNumber(aParameter, &a)) {
		printf("Invalid number \n");
		return;
	}
	putchar('\n');
	printf("B: ");
	char bParameter[20] = {0};
	scanf(bParameter);
	if (!parseNumber(bParameter, &b)) {
		printf("Invalid number \n");
		return;
	}
	putchar('\n');

	printf("C: ");
	char cParameter[20] = {0};
	scanf(cParameter);
	if (!parseNumber(cParameter, &c)) {
		printf("Invalid number \n");
		return;
	}
	putchar('\n');
	clear();
	printf("PLOTTER PROGRAM\n");

	cuadratic(c, b, a);
}