#include <stdio.h>
#include "testlib.h"

void ok()
{
    printf("Ok!\n");
}

void fail(char* errorMessage)
{
    printf("%s\n", errorMessage);
}