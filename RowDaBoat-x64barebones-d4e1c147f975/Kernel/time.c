#include "videoDriver.h"
#include <stdint.h>
#include <textDriver.h>
#include <time.h>

static uint64_t ticks = 0;
// static int cursorState = CURSOR_OFF;

void timer_handler() {}

int ticks_elapsed() { return ticks; }

int seconds_elapsed() { return ticks / 18; }
