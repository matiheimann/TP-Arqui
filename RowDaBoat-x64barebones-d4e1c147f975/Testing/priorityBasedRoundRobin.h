#ifndef PRIORITY_BASED_ROUND_ROBIN_H
#define PRIORITY_BASED_ROUND_ROBIN_H

#include "process.h"

#define HIGH_PRIORITY 0
#define MEDIUM_PRIORITY 1
#define LOW_PRIORITY 2

void initRoundRobin();
uint64_t schedule(uint64_t rsp);
void addProcessToRoundRobin(PCB* newProcess);

#endif