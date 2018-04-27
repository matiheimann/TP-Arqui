#include "queuelib.h"
#include "priorityBasedRoundRobin.h"

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

void* schedule()
{

}


