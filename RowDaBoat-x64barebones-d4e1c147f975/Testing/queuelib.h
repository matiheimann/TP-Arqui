#ifndef QUEUELIB_H
#define QUEUELIB_H

#include <stdint.h>

#define MAX_SIZE 256

typedef struct nodeCDT* nodeADT;

typedef struct nodeCDT
{
	void* stackPointer;
	//TODO
}nodeCDT;

typedef struct queueCDT* queueADT;

typedef struct queueCDT
{
	nodeCDT queue[MAX_SIZE];
    uint32_t rear;
    uint32_t front;
    uint32_t maxSize;
    uint32_t actualSize;
}queueCDT;

void initQueue(queueADT MyQueue);
void enqueueElement(queueADT myQueue, void * process);
void* dequeueElement(queueADT myQueue);
int isEmpty(queueADT myQueue);
int queueCurrentSize(queueADT myQueue);


#endif