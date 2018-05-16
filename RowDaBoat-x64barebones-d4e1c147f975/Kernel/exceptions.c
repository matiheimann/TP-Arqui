#include <exceptions.h>
#include <videoDriver.h>

static const exception exceptions[] = { zero_division, 0, 0, 0, overflow, 0,
                                        invalidOpCode };

void exceptionDispatcher(int exceptionID, uint64_t rsp, uint64_t rax,
                         uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi,
                         uint64_t rdi)
{
  exceptions[exceptionID](rsp, rax, rbx, rcx, rdx, rsi, rdi);
}

static void zero_division(uint64_t rsp, uint64_t rax, uint64_t rbx,
                          uint64_t rcx, uint64_t rdx, uint64_t rsi,
                          uint64_t rdi)
{
  printString("Zero division exception: \n");
  printExceptionStackFrame(rsp);
  printRegisters(rax, rbx, rcx, rdx, rsi, rdi);
}

static void overflow(uint64_t rsp, uint64_t rax, uint64_t rbx, uint64_t rcx,
                     uint64_t rdx, uint64_t rsi, uint64_t rdi)
{
  printString("Overflow exception: \n");
  printExceptionStackFrame(rsp);
  printRegisters(rax, rbx, rcx, rdx, rsi, rdi);
}

static void invalidOpCode(uint64_t rsp, uint64_t rax, uint64_t rbx,
                          uint64_t rcx, uint64_t rdx, uint64_t rsi,
                          uint64_t rdi)
{
  printString("Invalid opcode exception: \n");
  printExceptionStackFrame(rsp);
  printRegisters(rax, rbx, rcx, rdx, rsi, rdi);
}

void printExceptionStackFrame(uint64_t rsp)
{

  exceptionStackFrame* exceptionInfo = (exceptionStackFrame*)rsp;

  printString("Instruction pointer: ");
  printHex(exceptionInfo->instruction_pointer);
  printChar('\n');

  printString("Code segment: ");
  printHex(exceptionInfo->code_segment);
  printChar('\n');

  printString("CPU flags: ");
  printHex(exceptionInfo->cpu_flags);
  printChar('\n');

  printString("Stack pointer: ");
  printHex(exceptionInfo->stack_pointer);
  printChar('\n');

  printString("Stack segment: ");
  printHex(exceptionInfo->stack_segment);
  printChar('\n');
}

void printRegisters(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx,
                    uint64_t rsi, uint64_t rdi)
{

  printString("Registers: \n");

  printString("RAX: ");
  printHex(rax);
  printChar('\n');

  printString("RBX: ");
  printHex(rbx);
  printChar('\n');

  printString("RCX: ");
  printHex(rcx);
  printChar('\n');

  printString("RDX: ");
  printHex(rdx);
  printChar('\n');

  printString("RSI: ");
  printHex(rsi);
  printChar('\n');

  printString("RDI: ");
  printHex(rdi);
  printChar('\n');
}