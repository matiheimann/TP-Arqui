#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#define MAX_QTY_PROCESSES 512


#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4


typedef struct processContext {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rflags;
    uint64_t cr3; //en duda
    uint64_t rip;
}processContext;

typedef struct PCB {
    uint32_t pid;
    processContext context;
    uint8_t state;
    uint64_t stackPointer;
    int priority;
}PCB;

typedef struct processTable{
    PCB list[MAX_QTY_PROCESSES];
    uint32_t numberOfProcessesOnTable;
    uint32_t pidCounter;
}processTable;

void initProcessTable(processTable * table);
void startNewProcess(uint64_t rip);
PCB* addNewProcessToTable(uint64_t rip);
uint32_t getNextPid();


#endif