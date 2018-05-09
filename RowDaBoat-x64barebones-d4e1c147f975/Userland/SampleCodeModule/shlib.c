#include "shlib.h"	
#include <graphPlotterApp.h>
#include <sampleExceptions.h>

void printWelcomeMessage()
{
	printf("SHELL - G.L.M.J. LITE O.S.\n");
	printf("-----------------------------------------------------------------\n");
}




void printHelp(int argc, char** argc)
{
	printf("Los comandos disponibles son: \n");
	printf("help: presenta una lista de los comandos disonibles.\n");
	printf("echo [str]: imprime en pantalla el string pasado como parametro.\n");
	printf("time: presenta la fecha actual y la hora actual.\n");
	printf("graph: ejecuta un programa para graficar funciones.\n");
	printf("invalid opcode: genera una excepcion de tipo invalid opcode y se imprimen los registros.\n");
	printf("divide by cero: genera una excepcion de division por cero, y se imprimen los registros.\n");
	printf("exit: se sale de la terminal.\n");
	printf("clear: limpia todo el contenido de la pantalla.\n");
	putchar('\n');
}

int execute(char* command)
{
	if(strcmp(command, "exit")==0)
		return 1;

	if(startsWith(command, "echo ")) {
		printf(command+5);
		putchar('\n');
	}
	else if(strcmp(command, "clear")==0) {
		clear();
		printWelcomeMessage();
	}
	else if(strcmp(command, "--clear")==0) {
		clear();
		newProcess((void*)&printWelcomeMessage, 0, NULL);
	}
	else if(strcmp(command, "divide by cero")==0)
	{
		generate_divide_by_cero();
	}
	else if(strcmp(command, "--divide by cero")==0)
	{
		newProcess((void*)&generate_divide_by_cero, 0, NULL);	
	}
	else if(strcmp(command, "overflow")==0) 
	{
		generate_overflow();
	}
	else if(strcmp(command, "--overflow")==0) 
	{
		newProcess((void*)&generate_overflow, 0, NULL);
	}
	else if(strcmp(command, "invalid opcode")==0) 
	{
		generate_inavlid_opcode();
	}
	else if(strcmp(command, "--invalid opcode")==0) 
	{
		newProcess((void*)&generate_inavlid_opcode, 0, NULL);
	}
	else if(strcmp(command, "time")==0) 
	{
		displayTimeData();
	}
	else if(strcmp(command, "--time")==0) 
	{
		newProcess((void*)&displayTimeData, 0, NULL);
	}
	else if(strcmp(command, "help")==0) 
	{
		printHelp();
	}
	else if(strcmp(command, "help")==0) 
	{
		newProcess((void*)&printHelp, 0, NULL);
	}
	else if(strcmp(command, "graph")==0) 
	{
		graphPlotter();
		printWelcomeMessage();
	}
	else if(strcmp(command, "--graph")==0) 
	{
		newProcess((void*)&graphPlotter, 0, NULL);
		printWelcomeMessage();
	}
	else {
		printf("Invalid command, use help to see available commands.\n");
	}
	return 0;
}
		