
#include <printf.h>
#include <naiveConsole.h>
#include "queuelib.h"

#define position(x) ((x)%MAX_SIZE)

void initQueue(queueADT myQueue)
{
	myQueue->maxSize = MAX_SIZE;
	myQueue->rear = 0;
	myQueue->front = 0;
	myQueue->actualSize = 0;
}

int queueCurrentSize(queueADT myQueue)
{
	return myQueue->actualSize;
}

int isEmpty(queueADT myQueue)
{
	return (myQueue->actualSize == 0) ? 1 : 0;
}

void enqueueElement(queueADT myQueue, void* process)
{

	if(myQueue->actualSize < myQueue->maxSize)
	{
        myQueue->queue[position(myQueue->actualSize)].stackPointer = process;
        myQueue->actualSize++;
		myQueue->rear = position(myQueue->rear + 1);
	}
	else
	{
        ncPrint("The queue is full");
	}
	return;
}

void* dequeueElement(queueADT myQueue)
{
	nodeADT aux;
	if(isEmpty(myQueue)){
        ncPrint("The queue is empty\n");
		return 0;
	}

	void* processToPop = myQueue->queue[position(myQueue->front)].stackPointer;
	myQueue->front = position(myQueue->front + 1);
	myQueue->actualSize--;
	return processToPop;
}