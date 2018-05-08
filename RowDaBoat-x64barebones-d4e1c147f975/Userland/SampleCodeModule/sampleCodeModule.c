/* sampleCodeModule.c */
#include <stdlib.h>
#include <graphPlotterApp.h>
#include <sampleExceptions.h>


int main() {
	char end = 0;
	printf("SHELL - authors LORANT MIKOLAS, MATIAS HEIMANN & JOHNATHAN KATAN\n");
	printf("-----------------------------------------------------------------\n");
	while(!end){
		putchar('>');

		char command[100] = {0};
		scanf(command);

		if(strcmp(command, "exit")==0)
			end = 1;

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
			printf("help: presenta una lista de los comandos disonibles\n");
			printf("echo [str]: imprime en pantalla el string pasado como parametro\n");
			printf("time: presenta la fecha actual y la hora actual\n");
			printf("graph: ejecuta un programa para graficar funciones\n");
			printf("invalid opcode: genera una excepcion de tipo invalid opcode y se imprimen los registros\n");
			printf("divide by cero: genera una excepcion de division por cero, y se imprimen los registros\n");
			printf("exit: se sale de la terminal\n");
			printf("clear: limpia todo el contenido de la pantalla\n");
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
	exit();
	return 0;
}