#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

static void zero_division();
static void overflow();
static void invalidOpCode();

typedef void (* exception)();

#endif