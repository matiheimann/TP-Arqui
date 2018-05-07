#include "message.h"

#define MAXITEMS 256

typedef struct circularMessageBufferCDT {
  int head;
  int tail;
  int count;
  message buffer[MAXITEMS];
} circularMsgBufferCDT;

typedef struct circularMessageBufferADT * circularMessageBufferADT;

void initCirularBuffer(circularMessageBufferADT buffer);
void push(circularMessageBufferADT buffer, message msg);
message pop(circularMessageBufferADT messageBuffer);
