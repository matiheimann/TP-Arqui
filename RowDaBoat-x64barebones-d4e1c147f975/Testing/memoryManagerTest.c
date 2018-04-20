#include <stdio.h>
#include "memoryManagerTest.h"
#include "memoryManager.h"

char memory[MEMORY_SIZE];

void* page1;
void* page2;

void* firstPageToAllocate;
void* secondPageToAllocate;

void* testingMemoryBlock;

int main(int argc, char const *argv[])
{
	overlappingPagesTest();
	contiguousPagesTest();
	freeMemoryTest();
}

void overlappingPagesTest()
{
	givenAnEmptyMemory();
	givenTwoPagesToAllocate();

	whenBothPagesAreAllocated();

	thenBothPagesAreNotOverlapped();
}

void contiguousPagesTest()
{
	givenAnEmptyMemory();
	givenTwoPagesToAllocate();

	whenBothPagesAreAllocated();

	thenBothPagesAreContiguousInMemory();
}

void freeMemoryTest()
{
	givenAnAllocatedBlockOfMemory(sizeof(char)*AMOUNT_OF_MEMORY_TO_ALLOCATE);

	whenAllMemoryAllocatedIsFreed();

	thenNoMoreMemoryIsAllocated();
}

void givenAnEmptyMemory()
{
	initializeMemory(memory);
}

void givenTwoPagesToAllocate()
{
	firstPageToAllocate = page1;
	secondPageToAllocate = page2;
}

void givenAnAllocatedBlockOfMemory(int amount)
{
	initializeMemory(memory);
	testingMemoryBlock = allocate(amount);
}

void whenBothPagesAreAllocated()
{
	firstPageToAllocate = allocate(sizeof(char)*(PAGE_SIZE-1));
	secondPageToAllocate = allocate(sizeof(char)*(PAGE_SIZE-1));
}

void whenAllMemoryAllocatedIsFreed()
{
	deallocate(testingMemoryBlock);
}

void thenBothPagesAreNotOverlapped()
{
	if(pagesAreNotOverlapped(firstPageToAllocate, secondPageToAllocate))
	{
		printf("Overlapping Pages Test: SUCCESS! Pages are not overlapped\n");
		return;
	}

		printf("Overlapping Pages Test: ERROR! Allocated pages are overlapped\n");
}

void thenBothPagesAreContiguousInMemory()
{
	if(pagesAreContiguous(firstPageToAllocate, secondPageToAllocate))
	{
		printf("Contiguous Pages Test: SUCCESS! Pages are contiguous\n");
		return;
	}

	printf("Contiguous Pages Test: ERROR! Allocated pages are not contiguous\n");
}

void thenNoMoreMemoryIsAllocated()
{
	if(noMoreMemoryIsAllocated())
	{
		printf("Free Memory Test: SUCCESS! Memory was freed\n");
		return;
	}

	printf("Free Memory Test: ERROR! Memory was not successfully freed\n");
}

int pagesAreNotOverlapped(void* leftPage, void* rightPage)
{
	if(((char*)leftPage + PAGE_SIZE > (char*)rightPage)) //Pages are overlapped
	{
		return 0;
	}

	return 1;
}

int pagesAreContiguous(void* leftPage, void* rightPage)
{
	if(((char*)leftPage + PAGE_SIZE == (char*)rightPage)) //Pages are contiguous
	{
		return 1;
	}

	return 0;
}

int noMoreMemoryIsAllocated()
{
	testingMemoryBlock = allocate(sizeof(char)*1);
	deallocate(testingMemoryBlock);

	if(testingMemoryBlock-1 == memory)
	{
		return 1;
	}

	return 0;
}
