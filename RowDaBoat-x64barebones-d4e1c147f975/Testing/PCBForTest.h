#ifndef PCBFORTEST_H
#define PCBFORTEST_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct {
	uint64_t gs;
	uint64_t fs;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
	uint64_t base;
} stack;

typedef struct processContext {
	uint64_t rax;
	uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rbp;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rflags;
	uint64_t cr3; // en duda
	uint64_t rip;
} processContext;

typedef struct PCB {
	uint64_t allocatedMemoryAddress;
	uint32_t pid;
	uint32_t parentPid;
	processContext context;
	uint8_t state;
	uint64_t stackPointer;
	int priority;
} PCB;

#endif