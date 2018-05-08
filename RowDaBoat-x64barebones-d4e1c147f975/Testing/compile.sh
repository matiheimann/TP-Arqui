#!/bin/bash
nasm -f elf64 -o mutex_asm.o mutex.asm
gcc -c mutex.c mutexTesting.c mutex.h
gcc -o mutexTest mutex_asm.o mutexTesting.o mutex.o -lpthread

gcc -o messageHolderTest messageHolder.c messageHolder.h messageHolderTesting.c mutex_asm.o mutex.o
