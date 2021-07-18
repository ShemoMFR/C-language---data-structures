/******************************************************************************************
*Title: Circular Buffer 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdlib.h> /* malloc/ free */
#include <assert.h> /* assert */ 
#include <errno.h> /* errno */
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */

#include "cbuffer.h"

#define MIN_CAPACITY (1)
#define MIN2(A, B) ((A) < (B) ? (A) : (B))
#define MIN3(A, B, C) (MIN2(A, MIN2(B, C))) 

struct cbuffer
{
    size_t size;
    size_t read_index;
    size_t capacity;
    char buffer[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *cbuffer = (cbuffer_t *)malloc(offsetof(cbuffer_t, buffer) + capacity * sizeof(cbuffer->buffer[0]));
	
	assert(capacity >= MIN_CAPACITY);
	
	if (NULL == cbuffer)
	{
		return cbuffer;
	}
	
	cbuffer->capacity = capacity;
	cbuffer->size = 0;
	cbuffer->read_index = 0;
	
	return cbuffer;
}

void CBufferDestroy(cbuffer_t *c_buffer)
{
	assert(c_buffer);	
	
	c_buffer->capacity = 0;
	c_buffer->size = 0;
	c_buffer->read_index = 0;
	
	free (c_buffer);
	c_buffer = NULL;
}

int CBufferIsEmpty(const cbuffer_t *c_buffer)
{
	assert(c_buffer);
	return (0 == c_buffer->size);
}

size_t CBufferSize(const cbuffer_t *c_buffer)
{
	assert(c_buffer);
	return (c_buffer->size);
}

size_t CBufferFreeSpace(const cbuffer_t *c_buffer)
{
	assert(c_buffer);
	return (c_buffer->capacity - c_buffer->size);
}

ssize_t CBufferWrite(cbuffer_t *c_buffer, const void *src, size_t count)
{
	ssize_t BytesReturned = 0;
	size_t minValue = 0, write_index = 0;

	if (!c_buffer)
	{
		errno = EBADF;
		return -1;
	}
	
	write_index = (c_buffer->read_index + c_buffer->size) % 
							c_buffer->capacity;
	
	while (CBufferFreeSpace(c_buffer) && count)
	{
		minValue = MIN3(CBufferFreeSpace(c_buffer), count, 
					c_buffer->capacity - write_index);
		
		memcpy(c_buffer->buffer + write_index, src, minValue);
		
		src = (char *)src + minValue;
		
		BytesReturned += minValue;
		c_buffer->size += minValue;
		count -= minValue;
		write_index = (write_index + minValue) % c_buffer->capacity;
	} 
	
	return BytesReturned;
}

ssize_t CBufferRead(cbuffer_t *c_buffer, void *dest, size_t count)
{
	ssize_t BytesReturned = 0;
	size_t minValue = 0;
	
	if (!c_buffer)
	{
		errno = EBADF;	
		return -1;
	}

	while (!(CBufferIsEmpty(c_buffer)) && count)	
	{
		minValue = MIN3(c_buffer->size, count, c_buffer->capacity -
					 c_buffer->read_index);
		
		memcpy(dest, c_buffer->buffer + c_buffer->read_index, minValue);
		
		dest = (char *)dest + minValue;
		
		BytesReturned += minValue;
		c_buffer->size -= minValue;
		count -= minValue;
		c_buffer->read_index = (c_buffer->read_index + minValue) %
							c_buffer->capacity;
	} 
	
	return BytesReturned;
}








