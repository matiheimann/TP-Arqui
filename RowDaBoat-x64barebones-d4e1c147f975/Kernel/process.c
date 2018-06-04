#include "process.h"
#include "memoryManager.h"
#include "priorityBasedRoundRobin.h"
#include "videoDriver.h"
#include "kernelThread.h"

static processTable table;
static PCB *currentPCB;


uint32_t startNewProcess(uint64_t rip, int argc, char **argv)
{
	PCB *newProcess = addNewProcessToTable(rip, argc, argv);
	addThreadToRoundRobin(&(newProcess->threads[0]));
	return newProcess->pid;
}

PCB *addNewProcessToTable(uint64_t rip, int argc, char **argv)
{
	int rear = table.numberOfProcessesOnTable;
	if (rear == MAX_QTY_PROCESSES) {
		printString("No more slots in process table\n");
	}
	else
	{
		table.list[rear].pid = getNextPid();
		table.list[rear].parentPid =
		    (currentPCB == NULL) ? -1 : currentPCB->pid;

		initializeThreads(&(table.list[rear]));
		createThread(&(table.list[rear]), HIGH_PRIORITY, rip, argc, argv, MAIN_THREAD);
	
		table.numberOfProcessesOnTable++;

	}
	return &(table.list[rear]);
}

void initializeProcessLog() { currentPCB = NULL; }

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

stack *initializeStack(uint64_t rsp, uint64_t rip, int argc, char **argv)
{
	uint64_t newAddress = (uint64_t)rsp - (uint64_t)sizeof(stack);
	stack *newProcessStack = (stack *)newAddress;
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
	newProcessStack->rsi = (uint64_t)argv;
	newProcessStack->rdi = (uint64_t)argc;
	newProcessStack->rbp = 0x00D;
	newProcessStack->rdx = rip;
	newProcessStack->rcx = 0x00F;
	newProcessStack->rbx = 0x010;
	newProcessStack->rax = 0x011;
	newProcessStack->rip = rip;
	newProcessStack->cs = 0x008;
	newProcessStack->rflags = 0x202;
	newProcessStack->rsp = (uint64_t) & (newProcessStack->base);
	newProcessStack->ss = 0x000;
	newProcessStack->base = 0x000;
	return newProcessStack;
}

void setCurrentProcess(PCB *process)
{
	currentPCB = process;
}

PCB* getCurrentProcess() { return currentPCB; }


/*
int isProcessTerminated(uint32_t pid)
{

	PCB *process = getProcessPCB(pid);
	if (process->state == TERMINATED)
		return 1;
	return 0;
}
*/
PCB* getProcessPCB(int pid)
{
	int i;
	for (i = 0; i < table.numberOfProcessesOnTable; i++) {
		if (pid == table.list[i].pid) {
			return &(table.list[i]);
		}
	}
	printString("Process pid: ");
	printInt(pid);
	printString("not found in process table.\n");
	return NULL;
}

void setCurrentProcessState(int state) { getCurrentThread()->state = state; }



uint32_t getCurrentProcessPID() { return currentPCB->pid; }

void fillProcessesInfo(processesInfoTable *processes)
{
	int i;
	processes->numberOfProcessesOnTable = table.numberOfProcessesOnTable;
	for (i = 0; i < table.numberOfProcessesOnTable; i++) {
		processes->list[i].pid = table.list[i].pid;
		processes->list[i].priority = table.list[i].threads[0].priority;
		processes->list[i].state = table.list[i].threads[0].state;
		processes->list[i].sizeAllocated = 4 * 1024;
	}
}
