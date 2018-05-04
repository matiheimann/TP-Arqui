#include "process.h"
#include "priorityBasedRoundRobin.h"
#include "memoryManager.h"

static processTable table;

void startNewProcess()
{
    PCB newProcess;
    newProcess.stackPointer = allocate(0x0111);
    newProcess.state = NEW; 
    newProcess.priority = HIGH_PRIORITY;
    addProcessToTable(&newProcess);
    addProcessToRoundRobin(&newProcess);
}

void addProcessToTable(PCB * newProcess)
{
    newProcess->pid = getNextPid();
    table.list[table.numberOfPrcessesOnTable] = newProcess;
    table.numberOfPrcessesOnTable++;
}

void initProcessTable(processTable * table)
{
    table->pidCounter = 0;
    table->numberOfPrcessesOnTable = 0;
}

uint32_t getNextPid()
{
    uint32_t pid = table.pidCounter;
    table.pidCounter++;
    return pid;
}

