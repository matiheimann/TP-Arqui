#include <irqDispatcher.h>
#include <keyboard.h>
#include <stdint.h>
#include <time.h>

static const irq irqList[] = {int_20, int_21};

void irqDispatcher(uint64_t index) { irqList[index](); }

void int_20() { timer_handler(); }

void int_21() { keyboard_handler(); }
