#ifndef TEXT_DRIVER_H
#define TEXT_DRIVER_H

#include <stdint.h>

#define CURSOR_ON 1
#define CURSOR_OFF 0

void putString(char* s);
void putChar(char c);
void clear();
void putStringAt(uint32_t x, uint32_t y, char* s);
void newLine();
void putInt(int n);
int countDigits(int n);
void endOfScreen();
void deleteChar();
void putCursor();
void removeCursor();

#endif
