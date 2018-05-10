#include "mutex.h"

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

void destroyMutex(char* mutexId)
{
  if(mutexId == NULL)
  {
    return;
  }

  node* currentMutex = mutexList.first;
  node* previousMutex = NULL;

  while(currentMutex!=NULL)
  {
    if(strcmp(currentMutex->data->id, mutexId)==0)
    {

      if(previousMutex == NULL) //Current es el primer elemento de la lista
      {
        mutexList.first = currentMutex->next;
        deallocate(currentMutex->data);
        deallocate(currentMutex);
        return;
      }

      previousMutex->next = currentMutex->next;
      deallocate(currentMutex->data);
      deallocate(currentMutex);
      return;
    }

    previousMutex = currentMutex;
    currentMutex = currentMutex->next;
  }
}

mutex* retrieveMutex(char* mutexId)
{
  if(mutexId == NULL)
  {
    return NULL;
  }

  node* currentMutex = mutexList.first;

  while(currentMutex!=NULL)
  {
    if(strcmp(currentMutex->data->id, mutexId) == 0)
    {
      return currentMutex->data;
    }

    currentMutex = currentMutex->next;
  }

  return NULL;
}

mutex* createMutex(char* id)
{
  if(id == NULL)
  {
    return NULL;
  }

  mutex* mutexToAdd;
  node* nodeToAdd;
  node* currentMutex = mutexList.first;
  node* previousMutex = NULL;

  while(currentMutex!=NULL)
  {
    if(strcmp(currentMutex->data->id, id) == 0)
    {
      return NULL;
    }

    previousMutex = currentMutex;
    currentMutex = currentMutex->next;
  }

  mutexToAdd = allocate(1*sizeof(mutex));
  nodeToAdd = allocate(1*sizeof(node));

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
