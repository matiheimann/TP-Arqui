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
//		putchar(c);
//		printInt(c);
	}

	return c;
}

int scanf(char * buff){
	char c;
	int i = 0;
	while((c = getChar()) != '\n'){
		*(buff + i) = c;
		i++;
		putchar(c);
	}
	putchar('\n');
	return 0;
}

