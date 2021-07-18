/*****************************************************************************
*Title: dvector.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
******************************************************************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc/free */
#include <assert.h> /* assert */
#include "dvector.h" 

#define FACTOR (2)

enum end_process
{
	SUCCESS = 0, FAILED = 1, CHANGED = 2
};

struct vector
{
    void **elements;
    size_t capacity;
    size_t size;
};

vector_t *VectorCreate(size_t initial_capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	vector->capacity = initial_capacity;
	vector->size = 0;
	
	if (vector == NULL)
	{
		free(vector);
		return NULL;
	}
	
	vector->elements = (void **)malloc(sizeof(void *) * initial_capacity);
	
	if (vector->elements  == NULL)
	{
		free(vector->elements);
		vector->elements = NULL;
		free(vector);
		vector = NULL;
		return NULL;
	}
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(vector); 
	
	vector->capacity = 0;
	vector->size = 0;
	free(vector->elements);
	vector->elements = NULL;
	free(vector);
	vector = NULL;
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector); 
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{	
	assert(vector); 	
	return vector->capacity;
}

int VectorPushBack(vector_t *vector, void *element)
{

	vector->elements[vector->size] = element;
	assert(vector); 
	++vector->size;
		
	if (vector->size == vector->capacity)
	{
		VectorReserve(vector, vector->capacity * FACTOR);
		vector->capacity *= FACTOR;
	}
	
	return SUCCESS;
}

void VectorPopBack(vector_t *vector)
{
	int statut = 0;
	assert(vector); 
		
	if ((4 * vector->size) <= vector->capacity)
	{
		statut = VectorReserve(vector, vector->capacity * 2);
		vector->capacity = (vector->size * 2);		
	}	
	
	if (statut == FAILED)
	{
		return;
	}
	
	--vector->size;
		
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **ptr_temp = (void **)realloc(vector->elements, sizeof(void *) * (new_capacity));
	assert(vector);
		
	if (ptr_temp == NULL)
	{
		free(ptr_temp);
		ptr_temp = NULL;
		return FAILED;
	}
	
	vector->elements = ptr_temp;		
	
	vector->capacity = new_capacity;

	return SUCCESS;
}

void VectorSetElement(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	assert(index <= vector->capacity);	
	vector->elements[index] = element;
}

void *VectorGetElement(vector_t *vector,  size_t index)
{
	assert(vector);
	assert(index <= vector->capacity);
	return vector->elements[index];
}

int VectorShrinkToFit(vector_t *vector)
{
	int statut = 0;
	assert(vector);
	
	statut = VectorReserve(vector, vector->size);
	
	if (statut == FAILED)
	{
		return FAILED;
	}
	
	vector->capacity = vector->size;
	
	return SUCCESS;
}


















