#include <exceptions.h>
#include <videoDriver.h>

static const exception exceptions[] = {zero_division, 0, 0, 0, overflow, 0, invalidOpCode};

void exceptionDispatcher(int exceptionID, uint64_t rsp) {
	exceptions[exceptionID](rsp);
}

static void zero_division(rsp) {
	printString("Division por cero");
	printChar('\n');
	exceptionStackFrame * exceptionInfo = rsp;
}

static void overflow(rsp) {
	printString("overflow");
}

static void invalidOpCode(rsp) {
	printString("invalid opcode");
}