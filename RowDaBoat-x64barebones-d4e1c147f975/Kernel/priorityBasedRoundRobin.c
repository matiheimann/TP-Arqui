#include "queuelib.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"
#include "videoDriver.h"

static queueCDT highPriorityQueue;
static queueCDT mediumPriorityQueue;
static queueCDT lowPriorityQueue;
static queueADT priorityRings[3];
static PCB* currentPCB;
static int flag = 0;


void initRoundRobin()
{
    priorityRings[HIGH_PRIORITY] = &highPriorityQueue;
    priorityRings[MEDIUM_PRIORITY] = &mediumPriorityQueue;
    priorityRings[LOW_PRIORITY] = &lowPriorityQueue;
    initQueue(priorityRings[HIGH_PRIORITY]);
	initQueue(priorityRings[MEDIUM_PRIORITY]);
	initQueue(priorityRings[LOW_PRIORITY]);
}

void addProcessToRoundRobin(PCB * newProcess)
{
	printInt(newProcess->pid);printString("\n");
	flag = 1;
    enqueueElement(priorityRings[newProcess->priority], newProcess);
}


uint64_t schedule(uint64_t rsp)
{
	PCB* aux;
	currentPCB->stackPointer = rsp;
	currentPCB->state = READY;
	if(flag == 2)
	{
		enqueueElement(priorityRings[currentPCB->priority], currentPCB);
		
	}
	else if(flag == 1)
		flag++;
	
	if(!isEmpty(priorityRings[HIGH_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[HIGH_PRIORITY]);
		currentPCB = aux;
		currentPCB->state = RUNNING;

	}
	else if(!isEmpty(priorityRings[MEDIUM_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[MEDIUM_PRIORITY]);
		currentPCB = aux;
		currentPCB->state = RUNNING;
	}
	else if(!isEmpty(priorityRings[LOW_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[LOW_PRIORITY]);
		currentPCB = aux;
		currentPCB->state = RUNNING;
	}
	printInt(currentPCB->pid);printString("\n");
	printString("CURRENT SP FROM SCHEDULE: ");printHex(currentPCB->stackPointer);printString("\n");printString("CURRENT SP FROM ASM: ");
	return currentPCB->stackPointer;
}