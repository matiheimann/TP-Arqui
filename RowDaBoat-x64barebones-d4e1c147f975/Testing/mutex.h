#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include <stdlib.h>

#define LOCKED 1
#define UNLOCKED 0

typedef struct mutex
{
  char state;
  char id;
} mutex;

typedef struct node
{
  mutex* data;
  struct node* next;
} node;

typedef struct mutexLinkedList
{
  node* first;
} mutexLinkedList;

mutex* createMutex(char id);
mutex* retrieveMutex(char mutexId);
void destroyMutex(char mutexId);
void lock(mutex* mutexToLock);
void unlock(mutex* mutexToUnlock);

#endif
