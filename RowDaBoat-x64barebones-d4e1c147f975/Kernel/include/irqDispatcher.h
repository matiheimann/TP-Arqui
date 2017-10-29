#ifndef IRQ_DISPATCHER_H
#define IRQ_DISPATCHER_H

typedef void (*irq)();

static void int_20();
static void int_21();

#endif