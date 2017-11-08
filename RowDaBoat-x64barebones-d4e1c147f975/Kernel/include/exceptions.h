#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

static void zero_division();
static void overflow();
static void invalidOpCode();

typedef void (* exception)(uint64_t rsp);

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

typedef struct {
  uint64_t instruction_pointer;
  uint64_t code_segment;
  uint64_t cpu_flags;
  uint64_t stack_pointer;
  uint64_t stack_segment;
} exceptionStackFrame;

#pragma pack(pop)		/* Reestablece la alinceación actual */

#endif