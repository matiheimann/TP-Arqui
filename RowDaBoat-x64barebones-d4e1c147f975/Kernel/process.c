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
        table.list[current].stackPointer = (uint64_t)initializeStack((uint64_t) (allocate(0x0111) + 0x0111), rip, 0, NULL);
        table.numberOfProcessesOnTable++;
    }
    return &(table.list[current]);
}


void initializeProcessTable()
{
    table.pidCounter = 0;
    table.numberOfProcessesOnTable = 0;
}

uint32_t getNextPid()
{
    uint32_t pid = table.pidCounter;
    table.pidCounter++;
    return pid;
}

stack* initializeStack(uint64_t rsp, uint64_t rip, int argc, char ** argv)
{
    uint64_t newAddress = (uint64_t) rsp - (uint64_t) sizeof(stack);
    stack* newProcessStack =  (stack*)newAddress;
    newProcessStack->gs = 0x001;
    newProcessStack->fs = 0x002;
    newProcessStack->r15 = 0x003;
    newProcessStack->r14 = 0x004;
    newProcessStack->r13 = 0x005;
    newProcessStack->r12 = 0x006;
    newProcessStack->r11 = 0x007;
    newProcessStack->r10 = 0x008;
    newProcessStack->r9 = 0x009;
    newProcessStack->r8 = 0x00A;
    newProcessStack->rsi = (uint64_t) argc;
    newProcessStack->rdi = (uint64_t) argv;
    newProcessStack->rbp = 0x00D;
    newProcessStack->rdx = rip;
    newProcessStack->rcx = 0x00F;
    newProcessStack->rbx = 0x010;
    newProcessStack->rax = 0x011;
    newProcessStack->rip = rip;
    newProcessStack->cs = 0x008;
    newProcessStack->rflags = 0x202;
    newProcessStack->rsp = (uint64_t) &(newProcessStack->base);
    newProcessStack->ss = 0x000;
    newProcessStack->base = 0x000;
    return newProcessStack;
}

