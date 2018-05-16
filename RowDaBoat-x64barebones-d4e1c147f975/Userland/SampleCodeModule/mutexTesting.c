#include <mutexTesting.h>
#include <stdlib.h>

void mutexTest()
{
	lockAndUnlockTest();
	printf("\n");
	generateAndGetTest();
	printf("\n");
	deleteMutexTest();
	printf("\n");
	multiProcessSincronizationTest();
	exitProcess();
}

void lockAndUnlockTest()
{
	printf("Lock and unlock test:\n");

	mutex *m0 = generateMutex("m0");
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

	mutex *retreived = getMutex("hola");

	if (retreived == NULL) {
		printf("Mutex succesfully deleted\n");
	}
}

void multiProcessSincronizationTest()
{
	printf("Multiprocess sincronization with mutex test: \n");

	generateMutex("multiProcessSincronizationTest");
	newProcess((void *)&p1, 0, NULL);
	newProcess((void *)&p2, 0, NULL);
	newProcess((void *)&p3, 0, NULL);
	newProcess((void *)&p4, 0, NULL);
	newProcess((void *)&p5, 0, NULL);
}

void p1(int argc, char **argv)
{
	printf("P1 empieza\n");
	mutex *m = getMutex("multiProcessSincronizationTest");
	lockMutex(m);
	int j;
	for (j = 0; j < 100000000; j++)
		;
	printf("P1 termina\n");
	unlockMutex(m);
	exitProcess();
}

void p2(int argc, char **argv)
{
	printf("P2 empieza\n");
	mutex *m = getMutex("multiProcessSincronizationTest");
	lockMutex(m);
	int j;
	for (j = 0; j < 10000000; j++)
		;
	unlockMutex(m);
	printf("P2 termina\n");
	exitProcess();
}

void p3(int argc, char **argv)
{
	printf("P3 empieza\n");
	mutex *m = getMutex("multiProcessSincronizationTest");
	lockMutex(m);
	int j;
	for (j = 0; j < 10000000; j++)
		;
	unlockMutex(m);
	printf("P3 termina\n");
	exitProcess();
}

void p4(int argc, char **argv)
{
	printf("P4 empieza\n");
	mutex *m = getMutex("multiProcessSincronizationTest");
	lockMutex(m);
	int j;
	for (j = 0; j < 10000000; j++)
		;
	unlockMutex(m);
	printf("P4 termina\n");
	exitProcess();
}

void p5(int argc, char **argv)
{
	printf("P5 empieza\n");
	mutex *m = getMutex("multiProcessSincronizationTest");
	lockMutex(m);
	int j;
	for (j = 0; j < 10000000; j++)
		;
	unlockMutex(m);
	printf("P5 termina\n");

	deleteMutex("multiProcessSincronizationTest");
	exitProcess();
}
