#include <mutexTesting.h>
#include <stdlib.h>

char globalBuffer[500];

void mutexTest()
{
  /*lockAndUnlockTest();
  printf("\n");
  generateAndGetTest();
  printf("\n");
  deleteMutexTest();*/
  printf("\n");
  multiProcessSincronizationTest();
}

void lockAndUnlockTest()
{
  printf("Lock and unlock test:\n");

  mutex* m0 = generateMutex("m0");
	printf("Locking mutex...\n");
	lockMutex(m0);
	printf("Unlocking mutex\n");
	unlockMutex(m0);
	printf("Locking mutex again...\n");
	lockMutex(m0);
	printf("Unlocking mutex again...\n");
	unlockMutex(m0);

  deleteMutex(m0->id);
}

void generateAndGetTest()
{
  printf("Generate and get mutex test:\n");

  mutex *m1 = generateMutex("m1");
  mutex *m2 = getMutex("m1");

  printf("Getted mutex id: ");
  printf(m2->id);
  printf("\n");

  printf("Expected getted mutex id: ");
  printf(m1->id);
  printf("\n");

  deleteMutex(m1->id);
  deleteMutex(m2->id);
}

void deleteMutexTest()
{
  printf("Delete mutex test: \n");

  generateMutex("hola");
  deleteMutex("hola");

  mutex* retreived = getMutex("hola");

  if(retreived == NULL)
  {
    printf("Mutex succesfully deleted\n");
  }
}

void multiProcessSincronizationTest()
{
  mutex* m = generateMutex("multiProcessSincronizationTest");
  newProcess((void*)&p1, 0, NULL);
  newProcess((void*)&p2, 0, NULL);
}

void p1()
{
  printf("P1 empieza\n");
  mutex* m = getMutex("multiProcessSincronizationTest");
  lockMutex(m);
  int j;
  for(j=0; j<10000000; j++);
  printf("P1 termina\n");
  unlockMutex(m);
  exitProcess();
}

void p2()
{
  printf("P2 empieza\n");
  mutex* m = getMutex("multiProcessSincronizationTest");
  lockMutex(m);
  int j;
  for(j=0; j<10000000; j++);
  unlockMutex(m);
  printf("P2 termina\n");
  exitProcess();
}

void p3()
{
  mutex* m = getMutex("multiProcessSincronizationTest");
  lockMutex(m);
  int j;
  for(j=0; j<10000000; j++);
  unlockMutex(m);
  exitProcess();
}

void p4()
{
  mutex* m = getMutex("multiProcessSincronizationTest");
  lockMutex(m);
  int j;
  for(j=0; j<10000000; j++);
  unlockMutex(m);
  exitProcess();
}
