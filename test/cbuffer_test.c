/******************************************************************************************
*Title: Circular Buffer 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h> /* printf */
#include <string.h> /* strcmp*/
#include <stddef.h> /* size_t */
#include "cbuffer.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

static void TestCBuffer();
static void IntCompare(int input, int output, char *Test);

enum end_prog
{
	SUCCESS = 0, FAILED = 1
};

int main(void)
{
	TestCBuffer();
	
	return SUCCESS;
}

static void TestCBuffer()
{
	int empty = 0;
	size_t size = 0;
	ssize_t nbr_write = 0;
	ssize_t nbr_read = 0;
	size_t free_space = 0;
	char dest[10];
	
/*******************Create*********************/	
	
	cbuffer_t *cbuffer = CBufferCreate(8);
			
/*****************Is Empty*********************/

	printf(""KBLU"************** TEST ISEMPTY *********************"KNRM"\n");		
	empty = CBufferIsEmpty(cbuffer);
	IntCompare(empty, 1, "Empty");
	
/*****************Is Empty*********************/
	printf(""KBLU"************** TEST SIZE *********************"KNRM"\n");			
	size = CBufferSize(cbuffer);
	IntCompare(size, 0, "Size ");
	
/*****************Write***********************/
	printf(""KBLU"************** TEST WRITE *********************"KNRM"\n");	
	free_space = CBufferFreeSpace(cbuffer);	
	IntCompare(free_space, 8, "Current Free Space");
	nbr_write =  CBufferWrite(cbuffer, "Helllo", 6);
	IntCompare(nbr_write, 6, "Write 6 char");
	size = CBufferSize(cbuffer);
	IntCompare(size, 6, "Size after write");
	free_space = CBufferFreeSpace(cbuffer);	
	IntCompare(free_space, 2, "Current Free Space");
	
/*******************Read*********************/
	printf(""KBLU"************** TEST READ *********************"KNRM"\n");	
	nbr_read = CBufferRead(cbuffer, dest, 6);
	IntCompare(nbr_read, 6, "Number read");
	free_space = CBufferFreeSpace(cbuffer);	
	IntCompare(free_space, 8, "Current Free Space");
	size = CBufferSize(cbuffer);
	IntCompare(size, 0, "Size after write");
	IntCompare(strcmp(dest, "Helllo"), 0, "Dest after read");
	printf(""KGRN"SUCCES"KNRM" String after read : %s\n", dest);	
	
/****************DESTROY*********************/

	CBufferDestroy(cbuffer);	

}

static void IntCompare(int input, int output, char *Test)
{
	if (input == output)
	{
		printf(""KGRN"SUCCES"KNRM" %s test : returned %d\n", Test, output); 
	}
	
	else
	{
		printf(""KRED"ERROR"KNRM" %s test : expected %d returned %d\n"KNRM, Test, output, input);
	}
} 








