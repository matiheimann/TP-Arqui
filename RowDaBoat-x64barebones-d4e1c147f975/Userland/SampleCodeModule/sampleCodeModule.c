/* sampleCodeModule.c */
void print(char * string);
char * v = (char*)0xB8000;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	char * s = "Arquitectura de las computadoras";
	while(*s){
		*v = *s;
		v++;
		*v = 0;
		v++;
		s++;
	}

	print("Hola mundo");
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}