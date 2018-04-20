#ifndef MEMORY_MANAGER_TEST_H
#define MEMORY_MANAGER_TEST_H

#define PAGE_SIZE 4096 //Page size of 4KB
#define AMOUNT_OF_MEMORY_TO_ALLOCATE 1048576 //1MB

void contiguousPagesTest();
void overlappingPagesTest();
void freeMemoryTest();

void givenAnEmptyMemory();
void givenTwoPagesToAllocate();
void givenAnAllocatedBlockOfMemory(int amount);

void whenBothPagesAreAllocated();
void whenAllMemoryAllocatedIsFreed();

void thenBothPagesAreContiguousInMemory();
void thenBothPagesAreNotOverlapped();
void thenNoMoreMemoryIsAllocated();

int pagesAreContiguous(void* leftPage, void* rightPage);
int pagesAreNotOverlapped(void* leftPage, void* rightPage);
int noMoreMemoryIsAllocated();

#endif