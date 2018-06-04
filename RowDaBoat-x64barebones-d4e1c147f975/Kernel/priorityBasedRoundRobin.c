#include "priorityBasedRoundRobin.h"
#include "memoryManager.h"
#include "process.h"
#include "queuelib.h"
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

void addThreadToRoundRobin(TCB *newThread)
{
	newThread->state = READY;
	enqueueElement(priorityRings[newThread->priority], newThread);
}


uint64_t schedule(uint64_t rsp)
{
	TCB *current = getCurrentThread();
	

	

	if (current != NULL) {
		current->stackPointer = rsp;
		if (current->state != TERMINATED && current->state != WAITING &&
		    current->state != WAITINGPROCESS) {
			current->state = READY;
			enqueueElement(priorityRings[current->priority],
				       current);
		}
	}


	return getNextThreadRSP(rsp);
}

uint64_t getNextThreadRSP(uint64_t rsp)
{
	if (!isEmpty(priorityRings[HIGH_PRIORITY])) {
		setCurrentThread(dequeueElement(priorityRings[HIGH_PRIORITY]));
		return getCurrentThread()->stackPointer;
	} else if (!isEmpty(priorityRings[MEDIUM_PRIORITY])) {
		setCurrentThread( dequeueElement(priorityRings[MEDIUM_PRIORITY]));
		return getCurrentThread()->stackPointer;
	} else if (!isEmpty(priorityRings[LOW_PRIORITY])) {
		setCurrentThread(dequeueElement(priorityRings[LOW_PRIORITY]));
		return getCurrentThread()->stackPointer;
	} else if (getCurrentThread() != NULL) {
		printString("\nATTENTION: there are no processes to run. "
			    "\nShutting down...\n");
		while (1)
			; // FREEZE SYSTEM
		return getCurrentThread()->stackPointer;
	}
	
	
	return rsp;
}
