#include <mutexTesting.h>
#include <stdlib.h>

void mutexTest()
{
  lockAndUnlockTest();
  printf("\n");
  generateAndGetTest();
  printf("\n");
  deleteMutexTest();
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
