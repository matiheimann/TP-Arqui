#ifndef QUEUELIB_H
#define QUEUELIB_H

#include "PCBForTest.h"
#include <stdint.h>

#define MAX_SIZE 256

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct nodeCDT *nodeADT;

typedef struct nodeCDT {
	PCB *processControlBlock;
} nodeCDT;

typedef struct queueCDT *queueADT;

typedef struct queueCDT {
	nodeCDT queue[MAX_SIZE];
	uint32_t rear;
	uint32_t front;
	uint32_t maxSize;
	uint32_t actualSize;
} queueCDT;

void initQueue(queueADT MyQueue);
void enqueueElement(queueADT myQueue, PCB *process);
PCB *dequeueElement(queueADT myQueue);
int isEmpty(queueADT myQueue);
int queueCurrentSize(queueADT myQueue);

#endif