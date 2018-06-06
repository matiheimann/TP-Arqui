#include "stdlib.h"
#include "killThreadDemo.h"


void killThreadDemo()
{
	printf("Welcome to the kill thread demo. First this main thread \nwill create another that has while(1).\nThen it will kill it.\n");

	int id = createThread((void*)&infiniteThred, 0 , NULL);
	
	printf("Thread Created id ");
	printInt(id);
	printf("\n");
	for(int i =0; i < 100000; i++)
		printf("");
	killThread(getPid(),id);
	printf("\nThread killed\n");
	exitProcess();

}
void infiniteThred()
{
	printf("----Hi I was just created to die and print dots----\n");
	while(1)
		printf(".");
}