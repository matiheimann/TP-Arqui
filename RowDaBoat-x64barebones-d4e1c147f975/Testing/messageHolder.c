#include "messageHolder.h"

messageHolderLinkedList messageHolderList;
char messageMutexIdCounter;

void sendMessage(messageHolder* message, char* data, int size)
{
  lock(message->messageMutex);

  int i;

  for (i = 0; i < size; i++)
  {
    if (message->currentMessageIndex == MAX_MESSAGE_SIZE)
    {
      // Bloquear el proceso en el scheduler hasta que el receiver lo
      // desbloquee
      // blockProcess(getProcessId);
    }

    message->message[message->currentMessageIndex] = *(data + i);
    message->currentMessageIndex++;
  }

  // Avisarle al receiver que escribi cosas en el buffer y se puede desbloquear
  // del scheduler
  // en caso de que se haya bloqueado por estar vacio el buffer
  // unblockProcess(message->receiverPID);

  unlock(message->messageMutex);
}

void destroyMessageHolder(char* id)
{
  if (id == NULL)
  {
    return;
  }

  messageHolderNode* currentMessage = messageHolderList.first;
  messageHolderNode* previousMessage = NULL;

  while (currentMessage != NULL)
  {
    if (strcmp(currentMessage->data->id, id) == 0)
    {

      if (previousMessage == NULL) // Current es el primer elemento de la lista
      {
        messageHolderList.first = currentMessage->next;
        free(currentMessage->data);
        free(currentMessage);
        return;
      }

      previousMessage->next = currentMessage->next;
      free(currentMessage->data);
      free(currentMessage);
      return;
    }

    previousMessage = currentMessage;
    currentMessage = currentMessage->next;
  }
}

messageHolder* retrieveMessageHolder(char* id)
{
  if (id == NULL)
  {
    return NULL;
  }

  messageHolderNode* currentMessage = messageHolderList.first;

  while (currentMessage != NULL)
  {
    if (strcmp(currentMessage->data->id, id) == 0)
    {
      return currentMessage->data;
    }

    currentMessage = currentMessage->next;
  }

  return NULL;
}

messageHolder* createMessageHolder(char* id)
{
  if (id == NULL)
  {
    return NULL;
  }

  mutex* messageMutexToAdd;
  messageHolder* messageHolderToAdd;
  messageHolderNode* messageHolderNodeToAdd;
  messageHolderNode* currentMessage = messageHolderList.first;
  messageHolderNode* previousMessage = NULL;

  while (currentMessage != NULL)
  {
    if (strcmp(currentMessage->data->id, id) == 0)
    {
      return NULL;
    }

    previousMessage = currentMessage;
    currentMessage = currentMessage->next;
  }

  messageHolderToAdd = malloc(1 * sizeof(messageHolder));
  messageHolderNodeToAdd = malloc(1 * sizeof(messageHolderNode));
  messageMutexToAdd = createMutex(messageMutexIdCounter + 1);

  messageHolderToAdd->id = id;
  messageHolderToAdd->messageMutex = messageMutexToAdd;
  messageHolderToAdd->senderPID = -1;
  messageHolderToAdd->receiverPID = -1;
  messageHolderNodeToAdd->data = messageHolderToAdd;

  messageMutexIdCounter++;

  if (previousMessage == NULL)
  {
    messageHolderList.first = messageHolderNodeToAdd;
  }
  else
  {
    previousMessage->next = messageHolderNodeToAdd;
  }

  return messageHolderToAdd;
}
