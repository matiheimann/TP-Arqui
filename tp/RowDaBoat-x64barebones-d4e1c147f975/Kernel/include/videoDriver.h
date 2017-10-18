#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

void putString(char*  s);
void putChar(char c);
void clear();
void putStringAt(uint32_t x, uint32_t y, char*s);
void newLine();
void delete();

#endif