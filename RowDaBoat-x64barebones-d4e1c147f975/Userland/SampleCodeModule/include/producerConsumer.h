#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#define MAX_MESSAGES_TO_SEND 100

void producer(int argc, char **argv);
void consumer(int argc, char **argv);
void initializeProdcons(int argc, char **argv);

#endif