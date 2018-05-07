#include "queuelib.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"
#include "videoDriver.h"

static queueCDT highPriorityQueue;
static queueCDT mediumPriorityQueue;
static queueCDT lowPriorityQueue;
static queueADT priorityRings[3];
static PCB* currentPCB;



void initializeRoundRobin()
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
	//printString("\nAdd process to Round Robin: ");printInt(newProcess->pid);printString("\n");
    enqueueElement(priorityRings[newProcess->priority], newProcess);
}


uint64_t schedule(uint64_t rsp)
{
	currentPCB->stackPointer = rsp;
	currentPCB->state = READY;
	currentPCB->priority = HIGH_PRIORITY;
	enqueueElement(priorityRings[currentPCB->priority], currentPCB);
	if(!isEmpty(priorityRings[HIGH_PRIORITY]))
	{
		currentPCB = dequeueElement(priorityRings[HIGH_PRIORITY]);
		currentPCB->state = RUNNING;

	}
	else if(!isEmpty(priorityRings[MEDIUM_PRIORITY]))
	{
		currentPCB = dequeueElement(priorityRings[MEDIUM_PRIORITY]);
		currentPCB->state = RUNNING;
	}
	else if(!isEmpty(priorityRings[LOW_PRIORITY]))
	{
		currentPCB = dequeueElement(priorityRings[LOW_PRIORITY]);
		currentPCB->state = RUNNING;
	}
	//printString("\n Dequeue process from Round Robin: "); printInt(currentPCB->pid);printString("\n");
	return currentPCB->stackPointer;
}

void printStack(uint64_t rsp)
{
		for(uint64_t i = rsp; i < 17*8 + rsp; i = i+8)
		{
			printString("(");
			printInt(i);
			printString(": ");
			printInt((uint64_t)*((uint64_t*)i));
			printString(")");
		}
}