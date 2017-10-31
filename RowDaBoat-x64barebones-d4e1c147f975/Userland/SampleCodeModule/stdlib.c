void printf(char * str){
	print(str, strlen(str));
}

void putchar(char c) {
	print(&c, 1);
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

int countDigits(int n){
	int i = 1;
	while(n >= 10){
		n /=10;
		i++;
	}
	return i;
}

int strlen(char* str){
	int i = 0;
	while(*str){
		i++;
		str++;
	}
	return i;
}

int scanf(char * buff){

}

char getChar(){
	char c = 0;
	while(c==0) {
		scan(&c, 1);
	}
	return c;
}