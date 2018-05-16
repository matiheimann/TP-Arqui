#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

static void zero_division();
static void overflow();
static void invalidOpCode();
void printExceptionStackFrame(uint64_t rsp);
void printRegisters(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx,
                    uint64_t rsi, uint64_t rdi);

typedef void (*exception)(uint64_t rsp, uint64_t rax, uint64_t rbx,
                          uint64_t rcx, uint64_t rdx, uint64_t rsi,
                          uint64_t rdi);

#pragma pack(push)
#pragma pack(1)

typedef struct
{
  uint64_t instruction_pointer;
  uint64_t code_segment;
  uint64_t cpu_flags;
  uint64_t stack_pointer;
  uint64_t stack_segment;
} exceptionStackFrame;

#pragma pack(pop)

#endif