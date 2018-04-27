//
// Created by lorant on 27/04/18.
//

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