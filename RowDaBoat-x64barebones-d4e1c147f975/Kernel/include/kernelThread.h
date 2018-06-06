#ifndef KERNEL_THREAD_H
#define KERNEL_THREAD_H

#include <stdint.h>

#define MAX_QTY_THREADS 20
#define MAIN_THREAD 1
#define SECONDARY_THREAD 0


typedef struct threadContext {
	uint64_t rax;
	uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rbp;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rflags;
	uint64_t cr3; // en duda
	uint64_t rip;
} threadContext;

typedef struct TCB {
	void* pcb;
	void* parentTCB;
	uint64_t allocatedMemoryAddress;
	uint32_t id;
	threadContext context;
	char state;
	uint8_t mainThread;
	uint64_t stackPointer;
	int priority;
}TCB;



int createThread(void* pcb, int priority, uint64_t rip, int argc, char** argv, int mainFlag);
void setCurrentThread(TCB* thread);
TCB* getCurrentThread();
void wakeUpThread(TCB* thread);
char* waitThread(int id, int pid);
void killThread(int id, int pid);
void initializeThreads(void* pcb);
void initializeThreadsLog();
void setCurrentThreadState(int state);
void stopThreadWait(TCB* tcb);
void setCurrentThreadState(int state);
TCB* getThreadTCB(int pid, int id);
uint32_t getCurrentThreadID();
void terminateCurrentThread();

#endif
