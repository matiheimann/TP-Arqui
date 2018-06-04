#ifndef MUTEX_H
#define MUTEX_H

#include "memoryManager.h"
#include <lib.h>
#include <process.h>
#include <queuelib.h>
#include <stdint.h>

#define LOCKED 1
#define UNLOCKED 0

typedef struct mutex {
	char state;
	char *id;
	queueADT waitingThreads;
} mutex;

typedef struct node {
	mutex *data;
	struct node *next;
} node;

typedef struct mutexLinkedList {
	node *first;
} mutexLinkedList;

mutex *createMutex(char *id);
mutex *retrieveMutex(char *mutexId);
void destroyMutex(char *mutexId);
TCB *lock(mutex *mutexToLock);
void unlock(mutex *mutexToUnlock);
void addCurrentThreadToWaitingQueue(mutex *m);
void dequeueWaitingThread(mutex *m);

#endif
