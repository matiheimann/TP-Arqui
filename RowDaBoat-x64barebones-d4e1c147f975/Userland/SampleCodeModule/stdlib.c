extern int scan(char * str, int length);
extern int print(char * str, int length);


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

