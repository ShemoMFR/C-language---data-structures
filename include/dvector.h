/*****************************************************************************
*Title: dvector.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
******************************************************************************/
#ifndef __OL99_D_VECTOR_H__
#define __OL99_D_VECTOR_H__

#include <stddef.h>	/* size_t */

typedef struct vector vector_t;

/*********************function************************/

/*****************************************************************************/
/*
Decription: 		creating a new vector_t Vector; O(1)
Return Value:		returns a pointer to the new struct
Reviewer: Benjamin
*/
vector_t *VectorCreate(size_t initial_capacity);

/*****************************************************************************/
/*
Decription: 		freeing memory allocation of a Vector; O(1)
Reviewer: Jane
*/		
void VectorDestroy(vector_t *vector);	

/*****************************************************************************/
/*
Decription: 		adding a new element to the end of a VectorCreate, if 
					capacity is equal to size, vector is reallocated to capacity
					multiplied by growth 
					factor; O(1)
Return Value:		returns 0 successful and other if failed
Reviewer:  Benjamin
*/	
int VectorPushBack(vector_t *vector, void *element);

/*****************************************************************************/
/*
Decription: 		poping an element from the end of a Vector; O(1)
Reviewer: Jake
*/
void VectorPopBack(vector_t *vector);

/*****************************************************************************/
/* 
Decription: 		Re-allocate vector based on new_capacity. unspecified if 
					new_capacity is less than size. O(1)
Return Value:		returns 0 successful and other if failed
Reviewer: Benjamin
*/
int VectorReserve(vector_t *vector, size_t new_capacity);	

/*****************************************************************************/
/*
Decription: 		checking an amount of elements in Vector; O(1)
Return Value:		returns the number of elements as size_t
Reviewer: Jane
*/
size_t VectorSize(const vector_t *vector);	 

/*****************************************************************************/
/*
Decription: 		checking current capacity of Vector; O(1)
Return Value:		returns the number of elements the structure can hold
Reviewer: Jane
*/
size_t VectorCapacity(const vector_t *vector); 

/*****************************************************************************/
/* 
Decription: 		setting an specific element in a Vector.
					unspecified if index is bigger than size; O(1)
Reviewer: Jack
*/
void VectorSetElement(vector_t *vector, size_t index, void *element);

/*****************************************************************************/
/*
Decription: 		getting specific element from Vector; O(1)
Return Value:		returns the element as a void pointer
Reviewer: Jack
*/
void *VectorGetElement(vector_t *vector,  size_t index);

/*
Decription: 		reallocate memory exactly to the current size; O(1)
Return Value:		returns 0 if successful and other if failed
Reviewer: Jake
*/
int VectorShrinkToFit(vector_t *vector);	

/* Pops then checks if size is a quarter of capacity and if so shrink capacity by half 
Reviewer : Jack
*/
int AdvancedPop(vector_t *vector);

#endif	/* __OL99_D_VECOTR_H__ */


