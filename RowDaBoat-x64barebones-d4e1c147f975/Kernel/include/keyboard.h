#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define SIZE 128
#define RIGHT_SHIFT_PRESSED  0X36
#define RIGHT_SHIFT_RELEASED 0XB6
#define LEFT_SHIFT_PRESSED 0x2A
#define LEFT_SHIFT_RELEASED 0xAA

unsigned char consumeBuffer();
void keyboard_handler();
unsigned char read_port(char);
#endif