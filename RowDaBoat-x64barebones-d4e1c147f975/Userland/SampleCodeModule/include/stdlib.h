#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

#define MAX_MESSAGE_SIZE 200
#define MAX_QUEUE_SIZE 256

typedef struct processInfo
{
  int pid;
  long long sizeAllocated;
  char state;
  int priority;
} processInfo;

typedef struct processesInfoTable
{
  int numberOfProcessesOnTable;
  processInfo* list;
} processesInfoTable;

typedef struct processContext
{
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
} processContext;

typedef struct PCB
{
  uint64_t allocatedMemoryAddress;
  uint32_t pid;
  processContext context;
  uint8_t state;
  uint64_t stackPointer;
  int priority;
} PCB;

typedef struct nodeCDT* nodeADT;

typedef struct nodeCDT
{
  PCB* processControlBlock;
} nodeCDT;

typedef struct queueCDT* queueADT;

typedef struct queueCDT
{
  nodeCDT queue[MAX_QUEUE_SIZE];
  uint32_t front;
  uint32_t maxSize;
  uint32_t actualSize;
} queueCDT;

typedef struct mutex
{
  char state;
  char* id;
  queueADT waitingProcesses;
} mutex;

typedef struct messageHolder
{
  uint32_t senderPID;
  uint32_t receiverPID;
  char* id;
  char message[MAX_MESSAGE_SIZE];
  int currentMessageIndex;
  mutex* messageMutex;
} messageHolder;

void printf(char*);
int strlen(char*);
int scanf(char*);
char getChar();
void putchar(char);
void printInt(int a);
int countDigits(int n);
int parseNumber(char* s, double* d);
int isNumeric(char c);
void clear();
int strcmp(const char* s1, const char* s2);
int startsWith(const char* str, const char* start);
void* malloc(int size);
void free(void* ptr);
void exitProcess();
int newProcess(void* ptr, int argc, char** argv);
int getPid();
void lockMutex(mutex* m);
void ps();
void wait(int pid);

extern void clearScreen();
extern void displayTimeData();
extern int scan(char* str, int length);
extern int print(char* str, int length);
extern void* memoryAllocation(int size);
extern void memoryFree(void* ptr);
extern void leaveProcess();
extern int createProcess(void* ptr, int argc, char** argv);
extern int getProcessPid();
extern void getProcessesInfo(processesInfoTable* processes);
extern mutex* generateMutex(char* id);
extern mutex* getMutex(char* mutexId);
extern void deleteMutex(char* mutexId);
extern PCB* blockMutex(mutex* mutexToLock);
extern void unlockMutex(mutex* mutexToUnlock);
extern messageHolder* generateMessageHolder(char* id);
extern messageHolder* getMessageHolder(char* id);
extern void deleteMessageHolder(char* id);
extern void send(messageHolder* message, char* data, int size);
extern void receive(messageHolder* message, char* storageBuffer, int size);
extern int* waitProcess(int pid);

#endif
