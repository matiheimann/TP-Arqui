/* sampleCodeModule.c */
#include <stdlib.h>
#include <graphPlotterApp.h>

int main() {
	
	char exit = 0;
	printf("SHELL - authors LORANT MIKOLAS, MATIAS HEIMANN & JOHNATHAN KATAN\n");
	printf("-----------------------------------------------------------------\n");
	while(!exit){
		putchar('>');

		char command[100] = {0};
		scanf(command);

		if(strcmp(command, "exit")==0)
			exit = 1;

		else if(startsWith(command, "echo ")) {
			printf(command+5);
			putchar('\n');
		}

		else if(strcmp(command, "clear")==0) {
			clear();
			printf("SHELL - authors LORANT MIKOLAS, MATIAS HEIMANN & JOHNATHAN KATAN\n");
			printf("-----------------------------------------------------------------\n");
		}

		else if(strcmp(command, "divide by cero")==0) {
			generate_divide_by_cero();
		}

		else if(strcmp(command, "overflow")==0) {
			generate_overflow();
		}

		else if(strcmp(command, "invalid opcode")==0) {
			generate_inavlid_opcode();
		}

		else if(strcmp(command, "time")==0) {
			displayTimeData();
		}

		else if(strcmp(command, "help")==0) {
			printf("Los comandos disponibles son: \n");
			printf("(a completar...)");
			putchar('\n');
		}

		else if(strcmp(command, "graph")==0) {
			graphPlotter();
			printf("SHELL - authors LORANT MIKOLAS, MATIAS HEIMANN & JOHNATHAN KATAN\n");
			printf("-----------------------------------------------------------------\n");
		}

		else {
			printf("Invalid command, use help to see available commands");
			putchar('\n');
		}
	}

	clear();
	return 1;
}