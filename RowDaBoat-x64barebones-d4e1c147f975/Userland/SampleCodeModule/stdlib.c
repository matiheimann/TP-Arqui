#include <stdlib.h>

int strlen(char* str){
	int i = 0;
	while(*str){
		i++;
		str++;
	}
	return i;
}

int strcmp(const char* str1, const char* str2) {
	while(*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

int startsWith(const char* str, const char* start) {
	while(*str && *start) {
		if(*str != *start)
			return 0;
		str++;
		start++;
	}

	return 1;
}

void printf(char * str){
	print(str, strlen(str));
}

void putchar(char c) {
	print(&c, 1);
}

int countDigits(int n){
	int i = 1;
	while(n >= 10){
		n /=10;
		i++;
	}
	return i;
}

void printInt(int n){
	char s[20] = {0};
	int i = countDigits(n)-1;
	while(i >= 0){
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	printf(s);
}

char getChar(){
	char c = 0;
	while(c == 0) {
		scan(&c, 1);
	}

	return c;
}

int scanf(char * buff){
	char c;
	int i = 0;
	while((c = getChar()) != '\n'){
		if(c == '\b'){
			if(i != 0){
				i--;
				*(buff + i) = 0;
				putchar(c);
			}

		}
		else{
			*(buff + i) = c;
			i++;
			putchar(c);
		}
	}
	if(i!=0)
		putchar('\n');
	return i;
}

void clear() {
	clearScreen();
}

int parseNumber(char * s, double * d) {
	*d = 0;
	double i = 1;
	char postDot = 0;
	char isNegative = 0;
	if(*s == '-'){
		isNegative = 1;
		s++;	
	}
	while(*s != 0){
		if(!postDot){
			if(isNumeric(*s)){
				*d *= 10;
				*d += *s - '0';
			}
			else if(*s == '.'){
				postDot = 1;
				i = 0.1;
			}
			else{
				return 0;
			}
		}
		else{
			if(isNumeric(*s)){
				*d += i * ((*s) - '0');
				i /= 10; 
			}
			else{
				return 0;
			}
		}
		s++;
	}
	if(isNegative){
		*d *= -1;
	}
	return 1;
}

int isNumeric(char c){
	return (c >= '0' && c <= '9');
}

void* malloc(int size)
{
	return memoryAllocation(size);
}

void free(void* ptr)
{
	memoryFree(ptr);
}

void exit()
{
	exitProcess();
}

int newProcess(void* ptr)
{
	return createProcess(ptr);
}
	
int getPid()
{
	return getProcessPid();
}

void ps()
{
	int i , aux;
	processesInfoTable* processes = (processesInfoTable*)malloc(0x010000);
	
	getProcessesInfo((void*)processes);
	printf("Processes count:\n");
	printInt(processes->numberOfProcessesOnTable);
	printf("\n pid     | state   | memoryAllocation | priority\n");
	printf(" -------------------------------------------------\n");
	for(i = 0; i < processes->numberOfProcessesOnTable; i++)
	{
		aux = 8 - countDigits(processes->list[i].pid);
		putchar(' ');
		printInt(processes->list[i].pid);
		while(aux > 0)
		{
			putchar(' ');
			aux--;
		}
		if(processes->list[i].state == 0)
		{
			printf("| NEW     | ");
		}
		else if(processes->list[i].state == 1)
		{
			printf("| READY   | ");
		}
		else if(processes->list[i].state == 2)
		{
			printf("| RUNNING | ");
		}
		else if(processes->list[i].state == 3)
		{
			printf("| WAITING | ");
		}
		else
		{
			printf("|TERMINATED| ");
		}
		printInt(processes->list[i].sizeAllocated);
		printf("             | ");
		printInt(processes->list[i].priority);
		printf("\n");
	}
	free(processes);
	return;
}
