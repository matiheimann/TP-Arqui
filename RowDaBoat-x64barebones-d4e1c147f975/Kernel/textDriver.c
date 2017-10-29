/* Video driver */

#include "textDriver.h"
#include <stdint.h>


static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;
static const uint8_t* finalVideo = (uint8_t*)(0xB8000 + 80 * 25 * 2);

void putString(char*  s){
	while(*s){
		putChar(*s);
		s++;
	}
}

void deleteChar() {
	if(currentVideo!=video) {
		*(currentVideo-1) = 0;
		*(currentVideo-2) = 0;
		currentVideo -= 2;
	}
	if((currentVideo - video) % width != 0){
		while(*currentVideo == 0){
			if(currentVideo == video){
				return;
			}
			currentVideo-=2;
		}
		currentVideo += 2;
	}
}

void putInt(int n){
	char s[20] = {0};
	int i = countDigits(n)-1;
	while(i >= 0){
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	putString(s);
}

int countDigits(int n){
	int i = 1;
	while(n >= 10){
		n /=10;
		i++;
	}
	return i;
}

void putChar(char c){
	if(currentVideo >= video + (height) * (width*2)){
		endOfScreen();
	}

	if(c == '\n')
		newLine();
	else if(c == '\b') {
		deleteChar();
	}
	else {
		*currentVideo = c;
		*(currentVideo + 1) = 0x0F;
		currentVideo +=2;
	}
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

void endOfScreen(){
	for(int i = 0; i < height -1; i++){
		for(int j = 0; j < width*2; j++){
			*(video + i * (width * 2) + j ) = *(video + (i+1) * (width * 2) + j);
		}
	}
	for(int i = 0; i < width *2; i++){
		*(video + (height-1)*width*2 + i) = 0; 
	}
	currentVideo = video + (height-1)*width*2;
}
