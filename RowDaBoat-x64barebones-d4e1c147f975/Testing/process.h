#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#define MAX_QTY_PROCESSES 514

typedef struct processContext {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsp;
    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint32_t eflags;
    uint64_t cr3; //en duda
    uint64_t rip;
}processContext;

typedef struct PCB {
    uint32_t pid;
    processContext context;
    uint8_t state;
    void* stackPointer;
    int priority;
}PCB;

typedef struct processTable{
    PCB * list[MAX_QTY_PROCESSES];
    uint32_t numberOfPrcessesOnTable;
    uint32_t pidCounter;
}processTable;


void initProcessTable(processTable * table)
{
    table->pidCounter = 0;
    table->numberOfPrcessesOnTable = 0;
}


#endif
