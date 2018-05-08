#include "process.h"
#include "priorityBasedRoundRobin.h"
#include "memoryManager.h"
#include "videoDriver.h"

static processTable table;
static PCB* currentPCB;


uint32_t startNewProcess(uint64_t rip)
{
    PCB* newProcess = addNewProcessToTable(rip);
    addProcessToRoundRobin(newProcess);
    return newProcess->pid;
}

PCB* addNewProcessToTable(uint64_t rip)
{
    int rear = table.numberOfProcessesOnTable;
    if(rear == MAX_QTY_PROCESSES)
    {
        printString("No more slots in process table\n");

    }
    else
    {
        printString("ADDED PROCESS");
        table.list[rear].pid = getNextPid();
        table.list[rear].context.rip = rip;
        table.list[rear].state = NEW;
        table.list[rear].priority = HIGH_PRIORITY;
        table.list[rear].allocatedMemoryAddress = (uint64_t)allocate(0x0111);
        table.list[rear].stackPointer = (uint64_t)initializeStack(table.list[rear].allocatedMemoryAddress + 0x0111, rip, 0, NULL);
        table.numberOfProcessesOnTable++;
    }
    return &(table.list[rear]);
}



void initializeProcessLog()
{
     currentPCB = NULL;
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


void setCurrentProcess(PCB* process)
{
    currentPCB = process;
    currentPCB->state = RUNNING;
}

PCB* getCurrentProcess()
{
    return currentPCB;
}

void setCurrentProcessState(int state)
{
    currentPCB->state = state;
}


void terminateCurrentProcess()
{
    currentPCB->state = TERMINATED;
    deallocate((void*)currentPCB->allocatedMemoryAddress);
}

uint32_t getCurrentProcessPID()
{
    return currentPCB->pid;
}

void fillProcessesInfo(processesInfoTable* processes)
{
    int i;
    processes->numberOfProcessesOnTable = table.numberOfProcessesOnTable;
    for(i = 0; i < table.numberOfProcessesOnTable; i++)
    {
        processes->list[i].pid = table.list[i].pid;
        processes->list[i].priority = table.list[i].priority;
        processes->list[i].state = table.list[i].state;
        processes->list[i].sizeAllocated = 4*1024;
    }
}