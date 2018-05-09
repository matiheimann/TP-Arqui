#include "queuelib.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"
#include "memoryManager.h"
#include "videoDriver.h"

static queueCDT highPriorityQueue;
static queueCDT mediumPriorityQueue;
static queueCDT lowPriorityQueue;
static queueADT priorityRings[3];


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
	newProcess->state = READY;
    enqueueElement(priorityRings[newProcess->priority], newProcess);
}


uint64_t schedule(uint64_t rsp)
{	
	PCB* current = getCurrentProcess();
	if(current != NULL && current->state != TERMINATED && current->state != WAITING)
	{
		current->stackPointer = rsp;
		current->state = READY;
		enqueueElement(priorityRings[current->priority], current);
	}
	return getNextProcessRSP(rsp);
}

uint64_t getNextProcessRSP(uint64_t rsp)
{
	if(!isEmpty(priorityRings[HIGH_PRIORITY]))
	{
		setCurrentProcess(dequeueElement(priorityRings[HIGH_PRIORITY]));
		return getCurrentProcess()->stackPointer;
		
	}
	else if(!isEmpty(priorityRings[MEDIUM_PRIORITY]))
	{
		setCurrentProcess(dequeueElement(priorityRings[MEDIUM_PRIORITY]));
		return getCurrentProcess()->stackPointer;
		
	}
	else if(!isEmpty(priorityRings[LOW_PRIORITY]))
	{
		setCurrentProcess(dequeueElement(priorityRings[LOW_PRIORITY]));
		return getCurrentProcess()->stackPointer;
	}
	else if(getCurrentProcess() != NULL)
	{
		printString("\nERROR: there are no processes to run\n");
		return getCurrentProcess()->stackPointer;
	}
	return rsp;
}


