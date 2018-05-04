#include "process.h"
#include "../Kernel/include/memoryManager.h"
#include "priorityBasedRoundRobin.h"
#include <stdlib.h>

processTable table;

void startNewProcess()
{
    PCB newProcess;
    newProcess.stackPointer = malloc(0x1000);
    newProcess.state = 0; //TODO
    newProcess.priority = HIGH_PRIORITY;
    addProcessToTable(&newProcess);
    addProcessToRoundRobin(&newProcess);
}

void addProcessToTable(PCB * newProcess)
{
    newProcess->pid = table.pidCounter;
    table.list[table.numberOfPrcessesOnTable] = newProcess;
    table.pidCounter++;
    table.numberOfPrcessesOnTable++;
}
