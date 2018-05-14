#include "mutex.h"
#include <videoDriver.h>
#include <memoryManager.h>
#include <process.h>

extern void enter_region(mutex* m);
extern void leave_region(mutex* m);

mutexLinkedList mutexList;

PCB* lock(mutex* m)
{
  enter_region(m);
  return getCurrentProcess();
}

void unlock(mutex* m)
{
  leave_region(m);
}

void addCurrentProcessToWaitingQueue(mutex* m)
{
  PCB* currentProcess = getCurrentProcess();
  printString("Se agrega a la cola de espera al proceso de PID: ");
  printInt(currentProcess->pid);
  printString("\n");
  enqueueElement(m->waitingProcesses, currentProcess);
  setCurrentProcessState(WAITING);
}

void dequeueWaitingProcess(mutex* m)
{
  if(m->waitingProcesses->actualSize != 0)
  {
    PCB* waitingProcess = dequeueElement(m->waitingProcesses);
    printString("Se desencola de la cola de espera al proceso de PID: ");
    printInt(waitingProcess->pid);
    printString("\nEstado del proceso desencolado: ");
    printInt(waitingProcess->state);
    printString("\n");
    stopProcessWait(waitingProcess->pid);
  }
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

      if(previousMutex == NULL)
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
  queueADT waitingProcesses = allocate(1*sizeof(queueCDT));
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

  initQueue(waitingProcesses);
  mutexToAdd->waitingProcesses = waitingProcesses;
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
