#include "queuelib.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"

static queueCDT highPriorityQueue;
static queueCDT mediumPriorityQueue;
static queueCDT lowPriorityQueue;
static queueADT priorityRings[3];

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
