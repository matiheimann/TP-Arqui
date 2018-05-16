#include "testlib.h"
#include <stdio.h>

void ok() { printf("Ok!\n"); }

void fail(char *errorMessage) { printf("%s\n", errorMessage); }