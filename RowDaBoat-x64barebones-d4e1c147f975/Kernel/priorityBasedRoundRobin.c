#include "queuelib.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"

static queueCDT highPriorityQueue;
static queueCDT mediumPriorityQueue;
static queueCDT lowPriorityQueue;
static queueADT priorityRings[3];
static PCB* currentPCB;

void initRoundRobin()
{
    priorityRings[HIGH_PRIORITY] = &highPriorityQueue;
    priorityRings[MEDIUM_PRIORITY] = &mediumPriorityQueue;
    priorityRings[LOW_PRIORITY] = &lowPriorityQueue;
}

void addProcessToRoundRobin(PCB * newProcess)
{
    enqueueElement(priorityRings[newProcess->priority], newProcess);
}


uint64_t schedule(uint64_t rsp)
{
	PCB* aux;
	currentPCB->context.rsp = rsp;
	currentPCB->state = READY;
	enqueueElement(priorityRings[currentPCB->priority], currentPCB);
	if(!isEmpty(priorityRings[HIGH_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[HIGH_PRIORITY]);

	}
	else if(!isEmpty(priorityRings[MEDIUM_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[MEDIUM_PRIORITY]);
	}
	else if(!isEmpty(priorityRings[MEDIUM_PRIORITY]))
	{
		aux = dequeueElement(priorityRings[LOW_PRIORITY]);
	}
	currentPCB = aux;
	currentPCB->state = RUNNING;
	return currentPCB->context.rsp;
}