#include "../Kernel/include/memoryManager.h"
#include "memoryManagerTest.h"
#include <stdio.h>
#include <string.h>

char memory[MEMORY_SIZE];

void* page1;
void* page2;

void* firstPageToAllocate;
void* secondPageToAllocate;

void* testingMemoryBlock;

void* block1;
void* block2;
void* block3;

int sizeToAllocateForBlock1;
int sizeToAllocateForBlock2;
int sizeToAllocateForBlock3;

char* dataToStore1;
char* dataToStore2;
char* dataToStore3;

int main(int argc, char const* argv[])
{
  overlappingPagesTest();
  contiguousPagesTest();
  freeMemoryTest();
  allocateDifferentMemorySizesTest();
  storeDataInAllocatedBlocksTest();
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
  givenAnAllocatedBlockOfMemory(sizeof(char) * AMOUNT_OF_MEMORY_TO_ALLOCATE);

  whenAllMemoryAllocatedIsFreed();

  thenNoMoreMemoryIsAllocated();
}

void allocateDifferentMemorySizesTest()
{
  givenAnEmptyMemory();
  givenDifferentMemorySizesToAllocate();

  whenBlocksOfDifferentSizesAreAllocated();

  thenMemoryAdressForEachBlockIsReturned();
}

void storeDataInAllocatedBlocksTest()
{
  givenDataToStore();
  givenMultipleAllocatedBlocks();

  whenDataIsStoredInAllocatedBlocks();

  thenDataCanBeRetrievedFromBlocks();
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

void givenDifferentMemorySizesToAllocate()
{
  sizeToAllocateForBlock1 = BLOCK_TEST_SIZE_1;
  sizeToAllocateForBlock2 = BLOCK_TEST_SIZE_2;
  sizeToAllocateForBlock3 = BLOCK_TEST_SIZE_3;
}

void givenDataToStore()
{
  dataToStore1 = DATA_TO_STORE_1;
  dataToStore2 = DATA_TO_STORE_2;
  dataToStore3 = DATA_TO_STORE_3;
}

void givenMultipleAllocatedBlocks()
{
  initializeMemory(memory);
  block1 = allocate(sizeToAllocateForBlock1);
  block2 = allocate(sizeToAllocateForBlock2);
  block3 = allocate(sizeToAllocateForBlock3);
}

void whenBothPagesAreAllocated()
{
  firstPageToAllocate = allocate(sizeof(char) * (PAGE_SIZE - 1));
  secondPageToAllocate = allocate(sizeof(char) * (PAGE_SIZE - 1));
}

void whenAllMemoryAllocatedIsFreed()
{
  deallocate(testingMemoryBlock);
}

void whenBlocksOfDifferentSizesAreAllocated()
{
  block1 = allocate(sizeToAllocateForBlock1);
  block2 = allocate(sizeToAllocateForBlock2);
  block3 = allocate(sizeToAllocateForBlock3);
}

void whenDataIsStoredInAllocatedBlocks()
{
  memcpy(block1, dataToStore1, strlen(dataToStore1));
  memcpy(block2, dataToStore2, strlen(dataToStore2));
  memcpy(block3, dataToStore3, strlen(dataToStore3));
}

void thenBothPagesAreNotOverlapped()
{
  if (pagesAreNotOverlapped(firstPageToAllocate, secondPageToAllocate))
  {
    printf("SUCCESS!\n");
    return;
  }

  printf("ERROR!\n");
}

void thenBothPagesAreContiguousInMemory()
{
  if (pagesAreContiguous(firstPageToAllocate, secondPageToAllocate))
  {
    printf("SUCCESS!\n");
    return;
  }

  printf("ERROR!\n");
}

void thenNoMoreMemoryIsAllocated()
{
  if (noMoreMemoryIsAllocated())
  {
    printf("SUCCESS!\n");
    return;
  }

  printf("ERROR!\n");
}

void thenMemoryAdressForEachBlockIsReturned()
{
  int indexBlock1 = (char*)block1 - memory;
  int indexBlock2 = (char*)block2 - memory;
  int indexBlock3 = (char*)block3 - memory;

  if (checkIfValidBlockInMemory(indexBlock1) &&
      checkIfValidBlockInMemory(indexBlock1) &&
      checkIfValidBlockInMemory(indexBlock1))
  {
    printf("SUCCESS!\n");
    return;
  }

  printf("ERROR!\n");
}

void thenDataCanBeRetrievedFromBlocks()
{
  if (storedDataIsValid())
  {
    printf("SUCCESS!\n");
    return;
  }

  printf("ERROR!\n");
  return;
}

int pagesAreNotOverlapped(void* leftPage, void* rightPage)
{
  if (((char*)leftPage + PAGE_SIZE > (char*)rightPage)) // Pages are overlapped
  {
    return 0;
  }

  return 1;
}

int pagesAreContiguous(void* leftPage, void* rightPage)
{
  if (((char*)leftPage + PAGE_SIZE == (char*)rightPage)) // Pages are contiguous
  {
    return 1;
  }

  return 0;
}

int noMoreMemoryIsAllocated()
{
  testingMemoryBlock = allocate(sizeof(char) * 1);
  deallocate(testingMemoryBlock);

  if (testingMemoryBlock - 1 == memory)
  {
    return 1;
  }

  return 0;
}

int checkIfValidBlockInMemory(int indexOfBlockInMemory)
{
  return (indexOfBlockInMemory - 1) % SMALLEST_BLOCK_SIZE == 0;
}

int storedDataIsValid()
{
  int isValidBlock1 = strncmp(dataToStore1, block1, strlen(dataToStore1));
  int isValidBlock2 = strncmp(dataToStore2, block2, strlen(dataToStore2));
  int isValidBlock3 = strncmp(dataToStore3, block3, strlen(dataToStore3));

  return isValidBlock1 == 0 && isValidBlock2 == 0 && isValidBlock3 == 0;
}