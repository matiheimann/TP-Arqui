#include "stdlib.h"
#include "kernelThreadsDemo.h"

void kernelThreadsDemo(int argc, char** argv)
{
	printf("Hi i'm  a process pid ");
	printInt(getPid());
	printf("(main thread) and i'm gonna create 2 threads and share with them heap data:");
	printf("SECRET SHARED DATA\n");
	char** args = malloc(0xFFE);
	args[0] = "SECRET SHARED DATA";
	createThread((void*)&threadMessage1, 1, args);
	waitThread(0,0);
	createThread((void*)&threadMessage2, 1, args);
	waitThread(0,0);
	printf("End of demo\n");
	exitProcess();

}

void threadMessage1(int argc, char** argv)
{
	printf("----Hi i'm a thread and share: ");
	printf(argv[0]);
	printf(" with other threads.----\n");
	exitProcess();
}
void threadMessage2(int argc, char** argv)
{
	printf("----Hi i'm another thread and also share: ");
	printf(argv[0]);
	printf(" with other threads.----\n");
	exitProcess();
}