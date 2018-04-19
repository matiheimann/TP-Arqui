#include <stdio.h>
#include <math.h>

#define FREE 0
#define USED 1
#define PAGE_SIZE 4096
#define START_ADRESS_OF_FIRST_PAGE 0
#define ADDRESS_OF_SECOND_PAGE 4096

void allocateFirstPageTest();
void allocateTwoPagesTest();

void givenOnePageToAllocate();
void givenTwoPagesToAllocate();

void whenPageIsAllocated();
void whenTwoPagesAreAllocated();

void thenStartAdressOfFirstPageIsReturned();
void thenAdressOfFirstAllocatedPageIsReturned();

int allocatePage();

char pageByteMap[16]; //16 available pages
int endOfKernel;

int adressOfAllocatedPage;
int pagesToAllocate;

int main(int argc, char const *argv[])
{
	allocateFirstPageTest();
	allocateTwoPagesTest();
}

void allocateFirstPageTest()
{
	givenOnePageToAllocate();
	whenPageIsAllocated();
	thenStartAdressOfFirstPageIsReturned();
}

void allocateTwoPagesTest()
{
	givenTwoPagesToAllocate();
	whenTwoPagesAreAllocated();
	thenAdressOfFirstAllocatedPageIsReturned();
}

void givenOnePageToAllocate()
{
	pagesToAllocate = 1;
}

void givenTwoPagesToAllocate()
{
	pagesToAllocate = 2;
}

void whenPageIsAllocated()
{
	adressOfAllocatedPage = allocatePage();
}

void whenTwoPagesAreAllocated()
{
	adressOfAllocatedPage = allocatePage(pagesToAllocate);
	allocatePage();
}

void thenStartAdressOfFirstPageIsReturned()
{
	if(adressOfAllocatedPage == START_ADRESS_OF_FIRST_PAGE)
	{
		printf("OK!\n");
	}
	else
	{
		printf("Error, value received: %d, value expected: %d\n", adressOfAllocatedPage, START_ADRESS_OF_FIRST_PAGE);
	}
}

void thenAdressOfFirstAllocatedPageIsReturned()
{
	if(adressOfAllocatedPage == ADDRESS_OF_SECOND_PAGE)
	{
		printf("OK!\n");
	}
	else
	{
		printf("Error, value received: %d, value expected: %d\n", adressOfAllocatedPage, ADDRESS_OF_SECOND_PAGE);
	}
}

int allocatePage()
{
	int i = 0;
	while(pageByteMap[i] != FREE)
	{
		i++;
	}
	pageByteMap[i] = USED;
	return endOfKernel + (i*PAGE_SIZE);
}