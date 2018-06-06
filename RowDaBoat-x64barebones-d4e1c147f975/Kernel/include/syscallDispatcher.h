#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H

#define STDOUT 1
#define STDIN 0

#include "kernelThread.h"
#include <messageHolder.h>
#include <mutex.h>

typedef uint64_t (*syscall)(uint64_t p, uint64_t q, uint64_t r);

uint64_t syscallDispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx,
			   uint64_t rdx);
uint64_t write(uint64_t fd, uint64_t buffer, uint64_t count);
uint64_t read(uint64_t fd, uint64_t buffer, uint64_t count);
void clearScreen();
void paintPixel(uint64_t x, uint64_t y);
uint16_t getResolutionY();
uint16_t getResolutionX();
void printRTCInfo();
void *allocateMemory(uint64_t memoryToReserve);
void deallocateMemory(void *ptr);
void exitProcess();
uint32_t createNewProcess(void *ptr, int argc, char **argv);
uint32_t getpid();
void getProcesses(void *table);
mutex *createMutexSysCall(char *id);
mutex *retrieveMutexSysCall(char *mutexId);
void destroyMutexSysCall(char *mutexId);
TCB *lockSysCall(mutex *mutexToLock);
void unlockSysCall(mutex *mutexToUnlock);
messageHolder *createMessageHolderSysCall(char *id);
messageHolder *retrieveMessageHolderSysCall(char *id);
void destroyMessageHolderSysCall(char *id);
void sendMessageSysCall(messageHolder *message, char *data, int size);
void receiveMessageSysCall(messageHolder *message, char *storageBuffer,
			   int size);
char *wait(int pid);
void openAFile(char* filename);
void closeAFile(char* filename);
void readAFile(char* filename);
void writeAFile(char* filename, char* text);
void appendAFile(char* filename, char* text);
void waitForThread(int pid, int id);
void kill(int pid, int id);
int createNewThread(void *ptr, int argc, char **argv);
void showFile();
void createAFile(char* filename);
void deleteAFile(char* filename);

extern void _sti();

#endif
