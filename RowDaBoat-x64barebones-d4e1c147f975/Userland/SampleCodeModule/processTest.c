#include <stdlib.h>
#include "processTest.h"

void p1(){
	int pid = getPid();
	printf("Hi from process...\n");
	printInt(pid);
	while(1);

}
void p2(){
	int pid = getPid();
	printf("Hi from process...\n");
	printInt(pid);
	while(1);

}
