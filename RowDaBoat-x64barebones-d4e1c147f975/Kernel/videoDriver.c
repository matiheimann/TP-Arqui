
#include <videoDriver.h>
#include <textDriver.h>

static const VBEModeInfoBlock * vesaInfo =  (uint64_t*)0x0000000000005C00;
static uint32_t videoCursor = 0;


void putpixel(int x,int y) {
	if(validPixelPosition(x,y)) {
		uint8_t * position = vesaInfo->PhysBasePtr + ( x + y* vesaInfo->XResolution)*3;
	    position[0] = 0xFF;          
	    position[1] = 0xFF; 
	    position[2] = 0xFF; 
	}
}

void putBlackPixel(int x, int y){
	int8_t * position = vesaInfo->PhysBasePtr + ( x + y* vesaInfo->XResolution)*3;
	position[0] = 0x00;          
	position[1] = 0x00; 
	position[2] = 0x00; 
}

int validPixelPosition(int x, int y) {
	if(x < vesaInfo->XResolution && y < vesaInfo->YResolution && x>=0 && y>=0)
		return 1;

	return 0;
}

int validCharPosition(int x, int y) {
	if(x>=0 && y>=0 && x<vesaInfo->XResolution/CHAR_WIDTH && y<vesaInfo->YResolution/CHAR_HEIGHT)
		return 1;

	return 0;
}

void printChar(char c) {
	if (1) {
		int y = videoCursor / charsPerLine;
		int x = videoCursor % charsPerLine;
		unsigned char * char_map = pixel_map(c);

		for(int i = 0; i < CHAR_HEIGHT; i++) {
			unsigned char pixel = char_map[i];
			printCharLine(pixel, x*CHAR_WIDTH, (y*CHAR_HEIGHT+i));
		}
		videoCursor++;
	}
}
/*
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
*/
void endScreen(){
	for(int i = 0; i < (vesaInfo->YResolution - CHAR_HEIGHT); i++){
		for(int j = 0; j < (vesaInfo->XResolution) * 3; j++){
			*((uint8_t *)(vesaInfo->PhysBasePtr) + i * charsPerLine*CHAR_WIDTH * 3 + j) = *((uint8_t *)(vesaInfo->PhysBasePtr) + (i + CHAR_HEIGHT) * charsPerLine*CHAR_WIDTH*3 + j);
		}
	}
	for(int i = vesaInfo->YResolution - CHAR_HEIGHT; i < vesaInfo->YResolution; i++){
		for(int j = 0; j < vesaInfo->XResolution; j++){
			putBlackPixel(j, i);
		}
	}
	videoCursor -= charsPerLine; 
}
void blackOut(){
	for(int i = 0; i < vesaInfo->XResolution; i++){
		for(int j = 0; j < vesaInfo->YResolution; j++){
			putBlackPixel(i, j);
		}
	}
	videoCursor = 0;
}
void printCharLine(unsigned char line, int x, int y) {
	char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
	int j = 0;
	char aux;
	for (j = 0; j < CHAR_WIDTH; j++) {
		aux = line & mask[j];
		if (aux != 0) { 
			putpixel(x+j, y);
		}
	}
}

void printString(char*  s){
	while(*s){
		printChar(*s);
		s++;
	}
}/*
void printCursor() {
	if(currentVideo >= video + (height) * (width*2)){
		endOfScreen();
	}

	*currentVideo = ' ';
	*(currentVideo+1) = 0xFF;
}

void removeCursor() {
	if(currentVideo >= video + (height) * (width*2)){
		endOfScreen();
	}

	*currentVideo = ' ';
	*(currentVideo+1) = 0;
}

void deleteChar() {
	removeCursor();
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
	removeCursor();
	int i = currentVideo - video;
	currentVideo += width * 2 - i%(width*2);
	putCursor();
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

*/