
#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 1


static void zero_division();
static void overflow();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception == OVERFLOW_EXCEPTION_ID)
		overflow();
}

static void zero_division() {
	// Handler para manejar excepcíon
}

static void overflow(){
	// Handler para manejar excepcion
}