#ifndef MEMORY_MANAGER_TEST_H
#define MEMORY_MANAGER_TEST_H

#define PAGE_SIZE 4096			     // Page size of 4KB
#define AMOUNT_OF_MEMORY_TO_ALLOCATE 1048576 // 1MB
#define BLOCK_TEST_SIZE_1 5674
#define BLOCK_TEST_SIZE_2 8
#define BLOCK_TEST_SIZE_3 50000
#define DATA_TO_STORE_1 "dataToStore1"
#define DATA_TO_STORE_2 "dataToStore2"
#define DATA_TO_STORE_3 "dataToStore3"

void contiguousPagesTest();
void overlappingPagesTest();
void freeMemoryTest();
void allocateDifferentMemorySizesTest();
void storeDataInAllocatedBlocksTest();

void givenAnEmptyMemory();
void givenTwoPagesToAllocate();
void givenAnAllocatedBlockOfMemory(int amount);
void givenAllocatedBlocksOfDiferentSizes();
void givenDifferentMemorySizesToAllocate();
void givenDataToStore();
void givenMultipleAllocatedBlocks();

void whenBothPagesAreAllocated();
void whenAllMemoryAllocatedIsFreed();
void whenBlocksOfDifferentSizesAreAllocated();
void whenDataIsStoredInAllocatedBlocks();

void thenBothPagesAreContiguousInMemory();
void thenBothPagesAreNotOverlapped();
void thenNoMoreMemoryIsAllocated();
void thenMemoryAdressForEachBlockIsReturned();
void thenDataCanBeRetrievedFromBlocks();
void thenDataCanBeRetrievedFromBlocks();

int pagesAreContiguous(void *leftPage, void *rightPage);
int pagesAreNotOverlapped(void *leftPage, void *rightPage);
int noMoreMemoryIsAllocated();
int checkIfValidBlockInMemory(int indexInMemory);
int storedDataIsValid();

#endif