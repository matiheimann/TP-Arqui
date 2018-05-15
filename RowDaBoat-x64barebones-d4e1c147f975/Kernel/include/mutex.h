#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include "memoryManager.h"
#include <lib.h>
#include <queuelib.h>
#include <process.h>

#define LOCKED 1
#define UNLOCKED 0

typedef struct mutex {
  char state;
  char* id;
  queueADT waitingProcesses;
}mutex;

typedef struct node {
  mutex* data;
  struct node* next;
} node;

typedef struct mutexLinkedList {
  node* first;
} mutexLinkedList;

mutex* createMutex(char* id);
mutex* retrieveMutex(char* mutexId);
void destroyMutex(char* mutexId);
PCB* lock(mutex* mutexToLock);
void unlock(mutex* mutexToUnlock);
void addCurrentProcessToWaitingQueue(mutex* m);
void dequeueWaitingProcess(mutex* m);

#endif
