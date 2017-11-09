#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

static void zero_division();
static void overflow();
static void invalidOpCode();
void printExceptionStackFrame(uint64_t rsp);

typedef void (* exception)(uint64_t rsp);

#pragma pack(push)		
#pragma pack (1) 		

typedef struct {
  uint64_t instruction_pointer;
  uint64_t code_segment;
  uint64_t cpu_flags;
  uint64_t stack_pointer;
  uint64_t stack_segment;
} exceptionStackFrame;

#pragma pack(pop)	

#endif