#include "shlib.h"
#include "producerConsumer.h"
#include "fourProcessDemo.h"
#include <graphPlotterApp.h>
#include <sampleExceptions.h>

void printWelcomeMessage()
{
	printf("SHELL - G.L.M.J. LITE O.S.\n");
	printf("---------------------------------------------------------------"
	       "--\n");
}

void printWelcomeMessageProcess(int argc, char **argv)
{
	printWelcomeMessage();
	exitProcess();
}

void printHelpProcess(int argc, char **argv)
{
  printf("-------------------------------------------------------\n");
  printf("Los comandos disponibles son: \n");
  printf("help: presenta una lista de los comandos disonibles.\n");
  printf("echo [str]: imprime en pantalla el string pasado como parametro.\n");
  printf("time: presenta la fecha actual y la hora actual.\n");
  printf("graph: ejecuta un programa para graficar funciones.\n");
  printf("invalid opcode: genera una excepcion de tipo invalid opcode y se "
         "imprimen los registros.\n");
  printf("divide by cero: genera una excepcion de division por cero, y se "
         "imprimen los registros.\n");
  printf("exit: se sale de la terminal.\n");
  printf("clear: limpia todo el contenido de la pantalla.\n");
  printf("ps: lista informacion sobre los procesos: pid, estado, espacio alocado y prioridad.\n");
  printf("prodcons: productor consumidor con buffer acotado.\n");
  printf("four process demo: crea 4 procesos nuevo que imprimen un mensaje y los muestra\nen la tabla de procesos.\n");
  printf("\n");
  printf("Agregar el prefijo -- para ejecutar en paralelo. (por ejemplo --time).\n");
  printf("Tener en cuenta que se puede producir comportamiento inesperado dado \nque se compite por la salida.\n");
  printf("-------------------------------------------------------\n");
  putchar('\n');
  exitProcess();
}

void graphPlotterProcess(int argc, char **argv)
{
	graphPlotter();
	exitProcess();
}

void displayTimeDataProcess(int argc, char **argv)
{
	displayTimeData();
	exitProcess();
}

void psProcess(int argc, char **argv)
{
	ps();
	exitProcess();
}
void echoProcess(int argc, char **argv)
{
	printf(argv[0]);
	putchar('\n');
	exitProcess();
}

int execute(char *command)
{
	int pid;
	int flag = 0;

  if (strcmp(command, "exit") == 0)
    return 1;
  if (startsWith(command, "--"))
  {
    command += 2;
    flag = 1;
  }
  if (startsWith(command, "echo "))
  {
    char* args[1];
    args[0] = command + 5;
    pid = newProcess((void*)&echoProcess, 1, args);
  }
  else if (strcmp(command, "clear") == 0)
  {
    clear();
    pid = newProcess((void*)&printWelcomeMessageProcess, 0, NULL);
  }
  else if (strcmp(command, "divide by cero") == 0)
  {
    pid = newProcess((void*)&generate_divide_by_cero, 0, NULL);
  }
  else if (strcmp(command, "overflow") == 0)
  {
    pid = newProcess((void*)&generate_overflow, 0, NULL);
  }
  else if (strcmp(command, "invalid opcode") == 0)
  {
    pid = newProcess((void*)&generate_inavlid_opcode, 0, NULL);
  }
  else if (strcmp(command, "time") == 0)
  {
    pid = newProcess((void*)&displayTimeDataProcess, 0, NULL);
  }
  else if (strcmp(command, "help") == 0)
  {
    pid = newProcess((void*)&printHelpProcess, 0, NULL);
  }
  else if (strcmp(command, "graph") == 0)
  {
    pid = newProcess((void*)&graphPlotterProcess, 0, NULL);
  }
  else if (strcmp(command, "ps") == 0)
  {
    pid = newProcess((void*)&psProcess, 0, NULL);
  }
  else if (strcmp(command, "prodcons") == 0)
  {
    pid = newProcess((void*)&initializeProdcons, 0, NULL);
  }
  else if (strcmp(command, "four process demo") == 0)
  {
    pid = newProcess((void*)&fourProcessesDemo, 0, NULL);
  }
  else
  {
    printf("Invalid command, use help to see available commands.\n");
    return 0;
  }
  if (!flag)
  {
    wait(pid);
  }
  return 0;
}
