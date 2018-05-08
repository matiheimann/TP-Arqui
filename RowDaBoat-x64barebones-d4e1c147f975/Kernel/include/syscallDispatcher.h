#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H

#define STDOUT 1
#define STDIN 0

typedef uint64_t (* syscall)(uint64_t p, uint64_t q, uint64_t r);

uint64_t syscallDispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx);
uint64_t write(uint64_t fd, uint64_t buffer, uint64_t count);
uint64_t read(uint64_t fd, uint64_t buffer, uint64_t count);
void clearScreen();
void paintPixel(uint64_t x, uint64_t y);
uint16_t getResolutionY();
uint16_t getResolutionX();
void printRTCInfo();
void* allocateMemory(uint64_t memoryToReserve);
void deallocateMemory(void* ptr);
void exit();
uint32_t createNewProcess(void* ptr);
uint32_t getpid();
void getProcesses(void* table);

#endif