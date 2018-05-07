#include "mutex.h"
#include <stdlib.h>
#include <stdio.h>

extern void enter_region(mutex* m);
extern void leave_region(mutex* m);

mutexLinkedList mutexList;

void lock(mutex* m)
{
  enter_region(m);
}

void unlock(mutex* m)
{
  leave_region(m);
}

void destroyMutex(uint64_t mutexId)
{
  if(mutexId <= 0)
  {
    return;
  }

  node* currentMutex = mutexList.first;
  node* previousMutex = NULL;

  while(currentMutex!=NULL)
  {
    if(currentMutex->data->id == mutexId)
    {

      if(previousMutex == NULL) //Current es el primer elemento de la lista
      {
        mutexList.first = currentMutex->next;
        free(currentMutex->data);
        free(currentMutex);
        return;
      }

      previousMutex->next = currentMutex->next;
      free(currentMutex->data);
      free(currentMutex);
      return;
    }

    previousMutex = currentMutex;
    currentMutex = currentMutex->next;
  }
}

mutex* retrieveMutex(uint64_t mutexId)
{
  if(mutexId <=0)
  {
    return NULL;
  }

  node* currentMutex = mutexList.first;

  while(currentMutex!=NULL)
  {
    if(currentMutex->data->id == mutexId)
    {
      return currentMutex->data;
    }

    currentMutex = currentMutex->next;
  }

  return NULL;
}

mutex* createMutex(char id)
{
  if(id <= 0)
  {
    return NULL;
  }

  mutex* mutexToAdd;
  node* nodeToAdd;
  node* currentMutex = mutexList.first;
  node* previousMutex = NULL;

  while(currentMutex!=NULL)
  {
    if(currentMutex->data->id == id)
    {
      return NULL;
    }

    previousMutex = currentMutex;
    currentMutex = currentMutex->next;
  }

  mutexToAdd = malloc(1*sizeof(mutex));
  nodeToAdd = malloc(1*sizeof(node));

  mutexToAdd->state = UNLOCKED;
  mutexToAdd->id = id;
  nodeToAdd->data = mutexToAdd;

  if(previousMutex == NULL)
  {
    mutexList.first = nodeToAdd;
  }
  else
  {
    previousMutex->next = nodeToAdd;
  }

  return mutexToAdd;
}
