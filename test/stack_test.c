/*/******************************************************************************************
*Title: stack.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: Dev
*****************************************************************************************/
#include <stdio.h> /*printf */
#include <assert.h> /* assert */
#include "stack.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

static void TestStack();

enum end_process
{
	SUCCESS = 0, FAILED = 1, EXIT_PROG = 2
};

int main(void)
{
	TestStack();
		
	return SUCCESS;
}

void TestStack()
{
	stack_t *stack;
	size_t a = 10;
	size_t b = 15;
	size_t c = 20;
	stack = StackCreate(10);
	
	printf(""KBLU"------- STACK TEST -------"KNRM"\n");
	printf(""KGRN"SUCCES\n"KNRM"");
	StackPush(stack, &a);
	printf(""KGRN"SUCCES\n"KNRM"");
	StackPush(stack, &b);
	printf(""KGRN"SUCCES\n"KNRM"");
	StackPush(stack, &c);
	printf(""KBLU"Number of elements inside stack"KNRM" %lu\n", StackSize(stack));
	if (StackIsEmpty(stack) == 1)
	{
		printf(""KRED"The Stack is empty"KNRM"\n");
	}
	else
	{
		printf(""KBLU"The Stack is not empty"KNRM"\n");
	}
	printf(""KBLU"Current element : "KNRM"");
	printf("%lu\n", *(size_t *)StackPeek(stack));
	printf(""KGRN"SUCCES "KNRM"");
  	StackPop(stack);  
  	printf("Element Poped\n");
  	printf(""KBLU"Current element : "KNRM"");
	printf("%lu\n", *(size_t *)StackPeek(stack));
	printf(""KBLU"Capacity of stack : "KNRM"");
	printf("%lu\n", StackCapacity(stack));
	printf(""KBLU"Number of elements inside stack"KNRM" %lu\n", StackSize(stack));
	printf(""KGRN"SUCCES "KNRM"");
  	StackPop(stack);  
  	printf("Element Poped\n");	
	printf(""KBLU"Number of elements inside stack"KNRM" %lu\n", StackSize(stack));
	  
  	StackDestroy(stack);
}











