#include "kernelThread.h"
#include "memoryManager.h"
#include "process.h"
#include "videoDriver.h"
#include "priorityBasedRoundRobin.h"
#include "syscallDispatcher.h"

static TCB *currentTCB;

void createThread(void * pcb, int priority, uint64_t rip, int argc, char** argv, int mainFlag)
{
	TCB* threads = ((PCB*)pcb)->threads;
	int rear = ((PCB*)pcb)->numberOfThreads;
	if(rear == MAX_QTY_THREADS)
	{
		printString("No more threads available\n");
	}
	else
	{
		threads[rear].priority = priority;
		threads[rear].context.rip = rip;
		threads[rear].parentTCB =
		    (currentTCB == NULL) ? NULL : currentTCB;
		threads[rear].state = NEW;
		threads[rear].allocatedMemoryAddress = (uint64_t)allocate(0x0FFE);
		threads[rear].stackPointer = (uint64_t)initializeStack(
		threads[rear].allocatedMemoryAddress + 0x0FFE, rip, argc,
		    argv);
		
		threads[rear].id = ((PCB*)pcb)->idCounter;
		threads[rear].mainThread = mainFlag;
		threads[rear].pcb = pcb;
		((PCB*)pcb)->numberOfThreads++;
		((PCB*)pcb)->idCounter++;
		if(mainFlag == SECONDARY_THREAD)
		{
			addThreadToRoundRobin(&(threads[rear]));
		}
	}
}

void setCurrentThread(TCB *thread)
{
	setCurrentProcess((PCB*)(thread->pcb));
	currentTCB = thread;
	currentTCB->state = RUNNING;
}

TCB* getCurrentThread()
{
	return currentTCB;
}
void initializeThreads(void* pcb)
{
	((PCB*)pcb)->idCounter = 0;
	((PCB*)pcb)->numberOfThreads = 0;
}

void initializeThreadsLog() { currentTCB = NULL; }

void setCurrentThreadState(int state) { currentTCB->state = state; }

char* waitThread(int id, int pid)
{
	TCB* thread = getCurrentThread();
	thread->state = WAITINGPROCESS;
	return &(thread->state);
}

void wakeUpThread(TCB* thread)
{
	if(thread->state == WAITINGPROCESS)
	{
		addThreadToRoundRobin(thread);
	}
}

void killThread(int id, int pid)
{
	
	TCB* thread = getThreadTCB(pid, id);
	if(thread->state == READY || thread->state == RUNNING)
	{
		thread->state = TERMINATED;
		wakeUpThread(thread->parentTCB);
		deallocate((void *)thread->allocatedMemoryAddress);
		if(thread->id == currentTCB->id 
			&& ((PCB*)(thread->pcb)) == ((PCB*)currentTCB->pcb))
		{
			_sti();
			while(thread->state == TERMINATED);
		}
		return;
	}
	else
	{
		printString("Can't kill thread id ");
		printInt(id);
		printString(" pid ");
		printInt(pid);
		printString("\n");
	}
	return;
	
		
}

void terminateCurrentThread()
{
	currentTCB->state = TERMINATED;
	if (currentTCB->parentTCB == NULL) {
		printString("\nConfirming shuttdown...\n");
	} else {
		TCB* thread = currentTCB->parentTCB;
		if (thread->state == WAITINGPROCESS){
			addThreadToRoundRobin(thread);
		}
	}
	deallocate((void *)currentTCB->allocatedMemoryAddress);
}

void stopThreadWait(TCB* tcb)
{
	if (tcb->state == WAITING) {
		addThreadToRoundRobin(tcb);
		return;
	} else {
		printString("Process pid: ");
		printInt(((PCB*)(tcb->pcb))->pid);
		printString(" thread was not waiting. Why stop thread wait?\n");
	}
}

TCB* getThreadTCB(int pid, int id)
{
	int i;
	PCB* pcb = getProcessPCB(pid);
	for(i = 0 ; i < pcb->numberOfThreads; i++)
	{
		if(pcb->threads[i].id == id)
		{
			return &(pcb->threads[i]);
		}
	}
	printString("Thread id ");
	printInt(id);
	printString("of process pid ");
	printInt(pid);
	printString(" was not found.\n");
	return NULL;
}

uint32_t getCurrentThreadID()
{
	return currentTCB->id;
}