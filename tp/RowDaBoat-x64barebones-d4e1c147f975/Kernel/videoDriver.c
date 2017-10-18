/* Video driver */

#include "videoDriver.h"
#include <stdint.h>


static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;
static const finalVideo = (uint8_t*)(0xB8000 + 80 * 25 * 2);

void putString(char*  s){
	while(*s){
		if(*s == '\n')
			newLine();
		else
			putChar(*s);
		s++;
	}
}

void putChar(char c){
	*currentVideo = c;
	*(currentVideo + 1) = 0x0F;
	currentVideo +=2;
}

void clear(){
	uint8_t * i;
	for(i = video; i < finalVideo; i++){
		*(i) = 0;
	}
	currentVideo = video;
}

void putStringAt(uint32_t x, uint32_t y, char* s){
	if(x >= 0 && x < width && y >= 0 && y < height){
		currentVideo = video + (y * width*2) + x*2;
		putString(s);
	}
	else{
		char * s = "input error";
		putStringAt(0,24, s);
	}
}

void newLine(){
	int i = currentVideo - video;
	currentVideo += width * 2 - i%(width*2);
}

void delete() {
	if(currentVideo == video)
		return;

	currentVideo -= 2;
	*currentVideo = 0;
}