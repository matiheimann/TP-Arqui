#include <exceptions.h>
#include <videoDriver.h>

static const exception exceptions[] = {zero_division, 0, 0, 0, overflow, 0, invalidOpCode};

void exceptionDispatcher(int exceptionID) {
	exceptions[exceptionID]();
}

static void zero_division() {
	printString("Division por cero");
}

static void overflow() {

}

static void invalidOpCode() {

}