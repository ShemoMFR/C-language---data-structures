/******************************************************************************************
*Title: stack.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: Approved
*****************************************************************************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* free */
#include "stack.h"

struct stack
{
    void **elements;
    size_t capacity;
    size_t top_of_stack; 
}Stack;

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = &Stack;
	stack->capacity = capacity;
	stack->elements = (void **)malloc(sizeof(void *) * capacity);
	
	if (stack == NULL)
	{
		return NULL;
	}
	
	stack->top_of_stack = 0;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack->elements);	
	stack->elements = NULL;	
}

int StackIsEmpty(stack_t *stack)
{
	assert(stack);
	return (stack->top_of_stack == 0);
}

void StackPush(stack_t *stack, void *element)
{
	assert(stack);
    stack->elements[stack->top_of_stack] = element;
    ++stack->top_of_stack;     
}

void *StackPeek(stack_t *stack)
{
	assert(stack);
	return stack->elements[stack->top_of_stack - 1];
}

void StackPop(stack_t *stack)
{
	assert(stack);
	assert(stack->top_of_stack > 0);
	--stack->top_of_stack;	
}

size_t StackSize(stack_t *stack)
{
	assert(stack);
	return stack->top_of_stack;	
}

size_t StackCapacity(stack_t *stack)
{
	assert(stack);
	return stack->capacity;
}












