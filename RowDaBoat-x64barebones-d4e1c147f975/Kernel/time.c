#include <time.h>
#include <stdint.h>
#include <textDriver.h>

static uint64_t ticks = 0;
static int cursorState = CURSOR_OFF;

void timer_handler() {
	ticks++;
	if(ticks%18 == 0) {
		if(cursorState == CURSOR_OFF) {
			putCursor();
			cursorState = CURSOR_ON;
		} else {
			removeCursor();
			cursorState = CURSOR_OFF;
		}
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
