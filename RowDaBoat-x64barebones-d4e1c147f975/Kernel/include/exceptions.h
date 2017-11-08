#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

static void zero_division();
static void overflow();
static void invalidOpCode();

typedef void (* exception)(uint64_t rsp);

typedef struct {
  uint64_t instruction_pointer;
  uint64_t code_segment;
  uint64_t cpu_flags;
  uint64_t stack_pointer;
  uint64_t stack_segment;
} exceptionStackFrame;

#endif