#include <stdint.h>
#include <videoDriver.h>
#include <syscallDispatcher.h>
#include <keyboard.h>
#include <rtcDriver.h>
#include "memoryManager.h"
#include "process.h"

static const syscall syscalls[]={0, 0, 0, read, write, (syscall)clearScreen, 
	(syscall)paintPixel, (syscall)getResolutionX, (syscall)getResolutionY, 
	(syscall)printRTCInfo, (syscall)allocateMemory, (syscall)deallocateMemory, (syscall)exit, (syscall)createNewProcess, (syscall)getpid};


uint64_t syscallDispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx){
	
	return syscalls[rax](rbx, rcx, rdx);
}

uint64_t write(uint64_t fd, uint64_t buffer, uint64_t count){
	int i = 0;
	/*salida estandar*/
	if (fd == STDOUT){
		for(i=0; i < count ; i++){
			printChar(((char*)buffer)[i]);
		}
	}
	return i;
}

uint64_t read(uint64_t fd, uint64_t buffer, uint64_t count){
	int i;
	unsigned char * charBuffer = (unsigned char *) buffer;
		/*entrada estandar*/
	if(fd == STDIN){
		for(i=0; i < count ; i++){
			char c = consumeBuffer();
			charBuffer[i] = c;
		}
	}
	return i;
}

void clearScreen() {
	blackOut();
}

void paintPixel(uint64_t x, uint64_t y){
	putpixel(x,y);
}

uint16_t getResolutionY(){
	return getYres();
}

uint16_t getResolutionX(){
	return getXres();
}

void printRTCInfo() {
	displayTime();
}

void* allocateMemory(uint64_t memoryToReserve)
{
	return allocate(memoryToReserve);
}

void deallocateMemory(void* ptr)
{
	deallocate(ptr);
}

void exit()
{
	terminateCurrentProcess();
}

uint32_t createNewProcess(void* ptr)
{
	return startNewProcess((uint64_t)ptr);
}

uint32_t getpid()
{
	return getCurrentProcessPID();
}
