#include "queueTest.h"
#include "queuelib.h"
#include "testlib.h"
#include <stdio.h>
#include <string.h>

static queueCDT queue;
static queueADT queueToTest = &(queue);
void* elementToDeque;
void* elementToEnqueue;
void* elementDequed;

int testQueueSize = 3;
void* elementToEnqueueValue = "TestElement";
void* secondElementToEnqueueValue = "TestElement2";

int main()
{
  printf("Empty queue test\n");
  emptyQueueTest();

  printf("Enqueue element test\n");
  enqueueElementTest();

  printf("Dequeue element test\n");
  dequeueElementTest();

  printf("Dequeue one out of two element test\n");
  dequeueOneOutOfTwoElementsTest();
}

void enqueueElementTest()
{
  givenAQueue();
  givenAnElement();

  whenElementIsEnqueued();

  thenSizeIsEqualToOne();
}

void emptyQueueTest()
{
  givenAQueue();

  whenElementIsDequed();

  thenNullIsReturned();
}

void dequeueElementTest()
{
  givenAQueueWithOneElement();

  whenElementIsDequed();

  thenSizeIsEqualToZero();
}

void dequeueOneOutOfTwoElementsTest()
{
  givenAQueueWithTwoElements();

  whenElementIsDequed();

  thenTheFirstElementIsReturned();
}

void givenAQueue()
{
  initQueue(queueToTest);
}

void givenAnElement()
{
  elementToEnqueue = elementToEnqueueValue;
}

void givenAQueueWithOneElement()
{
  initQueue(queueToTest);
  enqueueElement(queueToTest, elementToEnqueue);
}

void givenAQueueWithTwoElements()
{
  initQueue(queueToTest);
  enqueueElement(queueToTest, elementToEnqueueValue);
  enqueueElement(queueToTest, secondElementToEnqueueValue);
}

void whenElementIsDequed()
{
  elementToDeque = dequeueElement(queueToTest);
}

void whenElementIsEnqueued()
{
  enqueueElement(queueToTest, elementToEnqueue);
}

void thenNullIsReturned()
{
  if (elementToDeque == NULL)
  {
    ok();
  }
  else
  {
    fail("Element dequeued expected to be null, but it is not null\n");
  }
}

void thenSizeIsEqualToOne()
{
  if (queueCurrentSize(queueToTest) == 1)
  {
    ok();
  }
  else
  {
    fail("Size obtained is not 1");
  }
}

void thenSizeIsEqualToZero()
{
  if (queueCurrentSize(queueToTest) == 0)
  {
    ok();
  }
  else
  {
    fail("Size obtained is not 0 \n");
  }
}

void thenTheFirstElementIsReturned()
{
  if (strcmp(elementToDeque, elementToEnqueueValue) == 0)
  {
    ok();
  }
  else
  {
    fail("Element dequed different from element expected \n");
  }
}