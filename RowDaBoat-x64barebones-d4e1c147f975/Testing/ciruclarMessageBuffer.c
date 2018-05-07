#include "circularMessageBuffer.h"

void initCirularBuffer(circularMessageBufferADT messageBuffer) {
  messageBuffer->size = 0;
  messageBuffer->front = -1;
  messageBuffer->rear = -1;
}

void enqueueMessage(circularMessageBufferADT messageBuffer, message msg) {
  if ((messageBuffer->front == 0 && messageBuffer->rear == messageBuffer->size-1) ||
          (messageBuffer->rear == (messageBuffer->front-1)%(messageBuffer->size-1)))
  {
      // queue is full !
      return;
  }

  else if (messageBuffer->front == -1) /* Insert First Element */
  {
      messageBuffer->front = messageBuffer->rear = 0;
      messageBuffer->buffer[rear] = msg;
  }

  else if (messageBuffer->rear == messageBuffer->size-1 && messageBuffer->front != 0)
  {
      messageBuffer->rear = 0;
      messageBuffer->buffer[messageBuffer->rear] = msg;
  }

  else
  {
      messageBuffer->rear++;
      messageBuffer->buffer[messageBuffer->rear] = msg;
  }
}


message dequeueMessage(circularMessageBufferADT messageBuffer) {
  if (messageBuffer->front == -1)
  {
      // queue is empty !
      return INT_MIN;
  }

  message data = messageBuffer->buffer[messageBuffer->front];
  messageBuffer->buffer[messageBuffer->front] = -1;
  if (messageBuffer->front == messageBuffer->rear)
  {
      messageBuffer->front = -1;
      messageBuffer->rear = -1;
  }
  else if (messageBuffer->front == messageBuffer->size-1)
      messageBuffer->front = 0;
  else
      messageBuffer->front++;

  return data;
}
