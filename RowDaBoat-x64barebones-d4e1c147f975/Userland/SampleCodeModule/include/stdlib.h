#ifndef STDLIB_H
#define STDLIB_H	
	void printf(char*);
	int strlen(char*);
	int scanf(char *);
	char getChar();
	void putchar(char);
	void printInt(int a);
	int countDigits(int n);
	int parseNumber(char * s, double * d);
	int isNumeric(char c);
	void clear();
	int strcmp(const char* s1, const char* s2);
	int startsWith(const char* str, const char* start);
	extern void clearScreen();
	extern void displayTimeData();
	extern int scan(char * str, int length);
	extern int print(char * str, int length);
#endif