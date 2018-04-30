
#include <videoDriver.h>


static const VBEModeInfoBlock * vesaInfo =  (VBEModeInfoBlock*)0x0000000000005C00;
static uint32_t videoCursor = 0;


void putpixel(int x,int y) {
	if(validPixelPosition(x,y)) {
		uint8_t * initialPosition = (uint8_t *)((uint64_t)vesaInfo->PhysBasePtr);
		uint8_t * position = (uint8_t *)(initialPosition + ( x + y* vesaInfo->XResolution)*3);
	    position[0] = 0xFF;          
	    position[1] = 0xFF; 
	    position[2] = 0xFF; 
	}
}

void putBlackPixel(int x, int y){
	uint8_t * position = (uint8_t *)( (uint8_t *)((uint64_t)vesaInfo->PhysBasePtr) + ( x + y* vesaInfo->XResolution)*3);
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
	if(videoCursor >= charsPerHeight*charsPerLine){
		endScreen();
	}

	if(c == '\n'){
		nLine();
	}
	else if(c == '\b'){
		//Borra aunque este en la primer posicion
		erase();
	}
	else{
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

void printInt(uint64_t n){
	char s[16] = {0};
	int i = countAllDigits(n)-1;
	while(i >= 0){
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}

	printString(s);
}

int countAllDigits(uint64_t n){
	int i = 1;
	while(n >= 10){
		n /=10;
		i++;
	}
	return i;
}

void printHex(uint64_t n){
	char s[16] = {0};
	int i = countHexDigits(n)-1;
	while(i >= 0){
		if(n%16 < 10){
			s[i] = n % 16 + '0';
		}
		else if(n%16 == 10){
			s[i] = 'A';
		}
		else if(n%16 == 11){
			s[i] = 'B';
		}
		else if(n%16 == 12){
			s[i] = 'C';
		}
		else if(n%16 == 13){
			s[i] = 'D';
		}
		else if(n%16 == 14){
			s[i] = 'E';
		}
		else if(n%16 == 15){
			s[i] = 'F';
		}
		else{
			s[i] = n%16 + '0';
		}
		n /= 16;
		i--;
	}
	printString("0x");
	printString(s);
}

int countHexDigits(uint64_t n){
	int i = 1;
	while(n >= 16){
		n /=16;
		i++;
	}
	return i;
}

void endScreen(){
	uint8_t * initialPosition = (uint8_t *)((uint64_t)vesaInfo->PhysBasePtr);
	for(int i = 0; i < (vesaInfo->YResolution - CHAR_HEIGHT); i++){
		for(int j = 0; j < (vesaInfo->XResolution) * 3; j++){
			*((uint8_t *)(initialPosition) + i * charsPerLine*CHAR_WIDTH * 3 + j) = *((uint8_t *)(initialPosition) + (i + CHAR_HEIGHT) * charsPerLine*CHAR_WIDTH*3 + j);
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
}

void nLine(){
	if(videoCursor/charsPerLine == charsPerHeight -1){
		endScreen();
	}									
	videoCursor += charsPerLine - videoCursor % charsPerLine;	
}

void erase() {
	if(videoCursor == 0)
		return;
	videoCursor --;
	for(int i = 0; i< CHAR_HEIGHT; i++){
		for(int j = 0; j < CHAR_WIDTH ; j++){
			putBlackPixel((videoCursor % charsPerLine) * CHAR_WIDTH + j, (videoCursor / charsPerLine) * CHAR_HEIGHT + i);
		}
	}
}

uint16_t getXres(){
	return vesaInfo->XResolution;
}

uint16_t getYres(){
	return vesaInfo->YResolution;
}






