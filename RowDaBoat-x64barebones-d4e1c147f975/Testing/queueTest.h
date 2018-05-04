#ifndef QUEUETEST_H
#define QUEUETEST_H

void enqueueElementTest();

void emptyQueueTest();

void dequeueElementTest();

void dequeueOneOutOfTwoElementsTest();

void givenAQueue();
void givenAnElement();
void givenAQueueWithOneElement();

void givenAQueueWithTwoElements();
void whenElementIsDequed();

void whenElementIsEnqueued();
void thenNullIsReturned();

void thenSizeIsEqualToOne();
void thenSizeIsEqualToZero();
void thenTheFirstElementIsReturned();

#endif