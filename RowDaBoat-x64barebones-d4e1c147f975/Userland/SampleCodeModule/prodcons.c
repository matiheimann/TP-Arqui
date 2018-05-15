#include <stdlib.h>

#define BUFFSIZE 100


void producer(int argc, char ** argv) {

  int produce = 100;
  mutex *canRead, *canWrite, *criticalZone;
  char *idRead = "R", *idWrite = "W", *idCZ = "Z";
  canRead = getMutex(idRead);
  canWrite = getMutex(idWrite);
  criticalZone = getMutex(idCZ);
  double auxP;

  parseNumber(argv[0], &auxP);
  int * buffer = (uint32_t)auxP;

  int pid = getPid();
  int elems = 0;
  int nextValue = 0;

  while (produce > 0) {
    lockMutex(canWrite);
    lockMutex(criticalZone);

    elems = buffer[0];
    nextValue = buffer[1];

    // los 2 primeros elementos del buffer estan reservados
    buffer[elems + 2] = nextValue;

    // en principio solo va agregando como nuevo elemento la cantidad de elemntos actuales
    // printf("produced data: %d, ", elems);
    // printf("by process: %d\n", pid);

    elems++;
    nextValue++;

    buffer[1] = nextValue;

    if (elems == 1) {
      unlockMutex(canRead);
      unlockMutex(criticalZone);
    }

    if (elems == BUFFSIZE) {
      unlockMutex(canRead);
      unlockMutex(criticalZone);
      lockMutex(canWrite);
    }

    unlockMutex(criticalZone);
    unlockMutex(canWrite);

    produce--;
  }
  exitProcess();
}

void consumer(int argc, char ** argv){

  mutex *canRead, *canWrite, *criticalZone;
  char *idRead = "R", *idWrite = "W", *idCZ = "Z";
  canRead = getMutex(idRead);
  canWrite = getMutex(idWrite);
  criticalZone = getMutex(idCZ);
  double auxP;

  parseNumber(argv[0], &auxP);
  int * buffer = (uint32_t)auxP;

  int pid = getPid();
  int elems = 0;

  while (1) {
    lockMutex(canRead);
    unlockMutex(criticalZone);

    elems = buffer[0];

    // elems = buffer[elems];
    // printf("consumed data: %d, ", elems);
    // printf("by process: %d\n", pid);

    elems--;

    buffer[0] = elems;

    if (elems == 0) {
      unlockMutex(canWrite);
      unlockMutex(criticalZone);
      lockMutex(canRead);
    }

    if (elems == BUFFSIZE - 1) {
      unlockMutex(canWrite);
      unlockMutex(criticalZone);
    }

    unlockMutex(criticalZone);
    unlockMutex(canRead);
  }
  exitProcess();
}

void prodcons() {

  printf("PRODUCER/CONSUMER SIMULATOR\n");

  mutex *canRead, *canWrite, *criticalZone;
  char *idRead = "R", *idWrite = "W", *idCZ = "Z";
  unsigned int elems = 0;

  int * buffer = malloc( (BUFFSIZE + 1) * sizeof(int));
  // se guarda en la posicion 0 la cantidad de elementos
  buffer[0] = 0;
  // se guarda en la posicion 1 un contador con el proximo numero a agregar
  buffer[1] = 0;

  char buffPointer[20];
  char * stringPointer;

  // stringPointer = intToString((uint32_t)buffer, (char *)buffPointer);
  char ** argv = malloc( 1 * sizeof(char *));
  argv[0] = stringPointer;


  unsigned int running = 1;
  canRead = generateMutex(idRead);
  canWrite = generateMutex(idWrite);
  // el consumidor comienza bloqueado ya que no hay nada que leer
  lockMutex(canRead);
  criticalZone = generateMutex(idCZ);

  while (running) {
    double a,b;

		putchar('\n');

    printf("set number of producers: \n");

  	char number[20] = {0};
  	scanf(number);
  	while(!parseNumber(number, &a)){
  		printf("Invalid number \n");
  		scanf(number);
  	}

    putchar('\n');

    printf("set number of consumers: \n");

  	scanf(number);
  	while(!parseNumber(number, &b)){
  		printf("Invalid number \n");
  		scanf(number);
  	}

    for (int i = 0; i < b; i++) {
        newProcess((void*)&consumer, 1, argv);
    }

    for (int i = 0; i < a; i++) {
      // le tengo que pasar por argumento la dir de memoria del buffer
      newProcess((void*)&producer, 1, argv);
    }

    char command[20] = {0};
    while (running) {

      putchar('>');
      scanf(command);
      if(strcmp(command, "add comsumer") == 0) {

        newProcess((void*)&consumer, 1, NULL);
      }
      if(strcmp(command, "remove comsumer") == 0) {

      }
      if(strcmp(command, "add producer") == 0) {

        newProcess((void*)&producer, 1, NULL);
      }
      if(strcmp(command, "remove producer") == 0) {

      }
      else if(strcmp(command, "exit") == 0) {
        exitProcess();
        return;
      }
      else {
        printf("Invalid command\n");
      }
    }

  }
  exitProcess();
}


char * intToString (unsigned int i, char * buf) {
  char *p = buf + strlen(buf);
  *p = 0;

  do {
	   *--p = '0' + i % 10;
  } while ((i /= 10) != 0);

  return p;
}
