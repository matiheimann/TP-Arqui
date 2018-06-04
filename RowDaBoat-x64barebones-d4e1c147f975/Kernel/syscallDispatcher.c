#include "memoryManager.h"
#include "process.h"
#include "fileSystem.h"
#include <keyboard.h>
#include <messageHolder.h>
#include <mutex.h>
#include <rtcDriver.h>
#include <stdint.h>
#include <syscallDispatcher.h>
#include <videoDriver.h>
#include "kernelThread.h"

static const syscall syscalls[] = {0,
				   0,
				   0,
				   read,
				   write,
				   (syscall)clearScreen,
				   (syscall)paintPixel,
				   (syscall)getResolutionX,
				   (syscall)getResolutionY,
				   (syscall)printRTCInfo,
				   (syscall)allocateMemory,
				   (syscall)deallocateMemory,
				   (syscall)exitProcess,
				   (syscall)createNewProcess,
				   (syscall)getpid,
				   (syscall)getProcesses,
				   (syscall)createMutexSysCall,
				   (syscall)retrieveMutexSysCall,
				   (syscall)destroyMutexSysCall,
				   (syscall)lockSysCall,
				   (syscall)unlockSysCall,
				   (syscall)createMessageHolderSysCall,
				   (syscall)retrieveMessageHolderSysCall,
				   (syscall)destroyMessageHolderSysCall,
				   (syscall)sendMessageSysCall,
				   (syscall)receiveMessageSysCall,
				   (syscall)wait,
				   (syscall)openAFile,
				   (syscall)closeAFile,
				   (syscall)readAFile,
				   (syscall)writeAFile,
				   (syscall)appendAFile};


uint64_t syscallDispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx,
			   uint64_t rdx)
{

	return syscalls[rax](rbx, rcx, rdx);
}

uint64_t write(uint64_t fd, uint64_t buffer, uint64_t count)
{
	int i = 0;
	/*salida estandar*/
	if (fd == STDOUT) {
		for (i = 0; i < count; i++) {
			printChar(((char *)buffer)[i]);
		}
	}
	return i;
}

uint64_t read(uint64_t fd, uint64_t buffer, uint64_t count)
{
	int i;
	unsigned char *charBuffer = (unsigned char *)buffer;
	/*entrada estandar*/
	if (fd == STDIN) {
		for (i = 0; i < count; i++) {
			char c = consumeBuffer();
			charBuffer[i] = c;
		}
	}
	return i;
}

void clearScreen() { blackOut(); }

void paintPixel(uint64_t x, uint64_t y) { putpixel(x, y); }

uint16_t getResolutionY() { return getYres(); }

uint16_t getResolutionX() { return getXres(); }

void printRTCInfo() { displayTime(); }

void *allocateMemory(uint64_t memoryToReserve)
{
	return allocate(memoryToReserve);
}

void deallocateMemory(void *ptr) { deallocate(ptr); }

void exitProcess() { terminateCurrentThread(); }

uint32_t createNewProcess(void *ptr, int argc, char **argv)
{
	return startNewProcess((uint64_t)ptr, argc, argv);
}

uint32_t getpid() { return getCurrentProcessPID(); }

void getProcesses(void *table)
{
	processesInfoTable *info = (processesInfoTable *)table;
	fillProcessesInfo(info);
}

mutex *createMutexSysCall(char *id) { return createMutex(id); }

mutex *retrieveMutexSysCall(char *mutexId) { return retrieveMutex(mutexId); }

void destroyMutexSysCall(char *mutexId) { destroyMutex(mutexId); }

TCB *lockSysCall(mutex *mutexToLock) { return lock(mutexToLock); }

void unlockSysCall(mutex *mutexToUnlock) { unlock(mutexToUnlock); }

messageHolder *createMessageHolderSysCall(char *id)
{
	return createMessageHolder(id);
}

messageHolder *retrieveMessageHolderSysCall(char *id)
{
	return retrieveMessageHolder(id);
}

void destroyMessageHolderSysCall(char *id) { destroyMessageHolder(id); }

void sendMessageSysCall(messageHolder *message, char *data, int size)
{
	_sti();
	sendMessage(message, data, size);
}

void receiveMessageSysCall(messageHolder *message, char *storageBuffer,
			   int size)
{
	_sti();
	receiveMessage(message, storageBuffer, size);
}

char* wait(int pid)
{
	TCB *current = getCurrentThread();
	current->state = WAITINGPROCESS;
	return &(current->state);
}

void openAFile(char* filename){ openFile(filename); }

void closeAFile(char* filename){ closeFile(filename); }

void readAFile (char* filename) { readFile(filename); }

void writeAFile(char* filename, char* text) { writeFile(filename, text); }

void appendAFile(char* filename, char* text) { appendFile(filename, text); }
