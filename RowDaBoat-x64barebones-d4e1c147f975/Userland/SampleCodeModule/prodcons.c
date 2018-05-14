#include <stdlib.h>

#define BUFFSIZE 100


void prodcons() {

  printf("PRODUCER/CONSUMER SIMULATOR\n");

  //necesito acceso a los mutex con una syscall
  // mutex *canRead, *canWrite;
  char idRead = 'R', idWrite = 'W';
  unsigned int elems = 0;

  int * buffer = malloc( (BUFFSIZE + 1) * sizeof(int));

  unsigned int running = 1;
  // canRead = createMutex(idRead);
  // canWrite = createMutex(idWrite);

  while (running) {
    double a,b;

		putchar('\n');

    printf("set number of producers: ");

  	char number[20] = {0};
  	scanf(number);
  	while(!parseNumber(number, &a)){
  		printf("Invalid number \n");
  		scanf(number);
  	}

    for (int i = 0; i < a; i++) {
      // le tengo que pasar por argumento la dir de memoria del buffer
      newProcess((void*)&producer, 0, NULL);
    }

    putchar('\n');

    printf("set number of consumers: ");

  	scanf(number);
  	while(!parseNumber(number, &b)){
  		printf("Invalid number \n");
  		scanf(number);
  	}

    for (int i = 0; i < b; i++) {
        newProcess((void*)&consumer, 0, NULL);
    }
    while (1);
    //
    // putchar('>');
    // scanf(command);
    // if(strcmp(command, "add comsumer") == 0) {
    //
    //   newProcess((void*)&consumer, 1, NULL);
    // }
    // if(strcmp(command, "remove comsumer") == 0) {
    //
    // }
    // if(strcmp(command, "add producer") == 0) {
    //
    //   newProcess((void*)&producer, 0, NULL);
    // }
    // if(strcmp(command, "remove producer") == 0) {
    //
    // }
    // else if(strcmp(command, "exit") == 0) {
    //   exitProcess();
    //   return;
    // }
    //
    // else {
    //   printf("Invalid command\n");
    // }

  }

  return 0;
}


void producer(int * buffer) {

  // mutex *canRead, *canWrite;
  // char idRead = 'R', idWrite = 'W';
  // canRead = retrieveMutex(idRead);
  // canWrite = retrieveMutex(idWrite);

  int pid = getPid();
  int elems = 0;

  while (1) {
    // lock(canWrite);
    // lock(canRead);

    elems = buffer[0];

    elems++;
    buffer[elems] = elems;
    // en principio solo va agregando como nuevo elemento la cantidad de elemntos actuales
    printf("produced data: %d, by process: %d\n", elems, pid);


    if (elems == BUFFSIZE) {
      // unlock(canRead);
      // lock(canWrite);
    }

    // unlock(canWrite);
    // unlock(canRead);

  }
  return NULL ;
}

void consumer(int * buffer){

  // mutex *canRead, *canWrite;
  // char idRead = 'R', idWrite = 'W';
  // canRead = retrieveMutex(idRead);
  // canWrite = retrieveMutex(idWrite);

  int pid = getPid();
  int elems = 0;

  while (1) {
    // lock(canRead);

    elems = buffer[0];

    // elems = buffer[elems];
    printf("consumed data: %d, by process: %d\n", elems, pid);

    elems--;

    buffer[0] = elems;

    if (elems + 1 == BUFFSIZE) {
      // unlock(canWrite);
    }

    // unlock(canRead);

  }
  return NULL ;
}
