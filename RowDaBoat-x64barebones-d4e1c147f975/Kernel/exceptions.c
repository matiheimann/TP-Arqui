#include <exceptions.h>
#include <videoDriver.h>

static const exception exceptions[] = {zero_division, 0, 0, 0, overflow, 0, invalidOpCode};

void exceptionDispatcher(int exceptionID, uint64_t rsp) {
	exceptions[exceptionID](rsp);
}

static void zero_division(rsp) {
	printString("Division por cero");
	printChar('\n');
	exceptionStackFrame * exceptionInfo = (uint64_t*) rsp;

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

static void overflow(rsp) {
	printString("overflow");
}

static void invalidOpCode(rsp) {
	printString("invalid opcode");
}