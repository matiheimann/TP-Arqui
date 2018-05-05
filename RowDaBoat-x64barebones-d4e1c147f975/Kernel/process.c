#include "process.h"
#include "priorityBasedRoundRobin.h"
#include "memoryManager.h"
#include "videoDriver.h"

static processTable table;


void startNewProcess(uint64_t rip)
{
    PCB* newProcess = addNewProcessToTable(rip);
    addProcessToRoundRobin(newProcess);
}

PCB* addNewProcessToTable(uint64_t rip)
{
    int current = table.numberOfProcessesOnTable;
    if(current == MAX_QTY_PROCESSES)
    {
        printString("No more slots in process table\n");

    }
    else
    {
        table.list[current].pid = getNextPid();
        table.list[current].state = NEW;
        table.list[current].priority = HIGH_PRIORITY;
        table.list[current].stackPointer = (uint64_t) allocate(0x0111);
      
        ((uint64_t*)(table.list[current].stackPointer))[16*8] = (uint64_t)rip;
        ((uint64_t*)(table.list[current].stackPointer))[15*8]= (uint64_t)0x206;
        
        table.numberOfProcessesOnTable++;
    }
    return &(table.list[current]);
}

void initProcessTable(processTable * table)
{
    table->pidCounter = 0;
    table->numberOfProcessesOnTable = 0;
}

uint32_t getNextPid()
{
    uint32_t pid = table.pidCounter;
    table.pidCounter++;
    return pid;
}

