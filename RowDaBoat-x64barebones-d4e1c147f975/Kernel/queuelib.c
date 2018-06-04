
#include "queuelib.h"
#include "videoDriver.h"

#define position(x) ((x) % MAX_SIZE)

void initQueue(queueADT myQueue)
{
	myQueue->front = 0;
	myQueue->actualSize = 0;
	myQueue->maxSize = MAX_SIZE;
}

int queueCurrentSize(queueADT myQueue) { return myQueue->actualSize; }

int isEmpty(queueADT myQueue) { return (myQueue->actualSize == 0) ? 1 : 0; }

void enqueueElement(queueADT myQueue, TCB *thread)
{
	if (myQueue->actualSize < myQueue->maxSize) {
		myQueue->queue[position(myQueue->front + myQueue->actualSize)]
		    .thread = thread;
		myQueue->actualSize++;
	} else {
		printString("The queue is full\n");
	}
	return;
}

TCB *dequeueElement(queueADT myQueue)
{
	if (isEmpty(myQueue)) {
		printString("The queue is empty\n");
		return 0;
	}

	TCB *threadToPop =
	    myQueue->queue[position(myQueue->front)].thread;
	myQueue->front = position(myQueue->front + 1);
	myQueue->actualSize--;
	return threadToPop;
}
