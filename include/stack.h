/******************************************************************************************
*Title: stack.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: Dev
*****************************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>	/*size_t */

typedef struct stack stack_t;

/*********************function************************/

/* Decription: creating a new stack_t stack; */
/* if create fails, returns NULL pointer */
stack_t *StackCreate(size_t capacity);


/* Decription: freeing memory allocation of the stack; */
void StackDestroy(stack_t *stack);	


/* Decription: adding a new element to the top of the stack; */
void StackPush(stack_t *stack, void *element);


/* Decription: poping an element from the top of the stack; */
void StackPop(stack_t *stack);


/* Decription: peeks at the element on the top of the stack; */
void *StackPeek(stack_t *stack);	 


/* Decription: getting current number of elements inside stack; */
size_t StackSize(stack_t *stack);	 


/* Decription: checking if the stack contains any elements; */
int StackIsEmpty(stack_t *stack);


/* Decription: returns number of elements that can be pushed onto the stack ; */
size_t StackCapacity(stack_t *stack); 

#endif /* __STACK_H__ */

