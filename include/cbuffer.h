/******************************************************************************************
*Title: Circular Buffer 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#ifndef __OL99_CBUFFER_H__
#define __OL99_CBUFFER_H__

#include <sys/types.h> /* size_t, ssize_t */

typedef struct cbuffer cbuffer_t;
/*********************function************************/


/*****************************************************************************
Decription: Creates Circular Buffer and returns pointer to it. O(1)
Input: Capacity of buffer (number of bytes)
Return Value: NULL if fails to allocate or pointer to cbuffer if succeeds.
Reviewer = Benjamin.
*************/

cbuffer_t *CBufferCreate(size_t capacity);

/*****************************************************************************
Decription: Frees allocated space for Circular Buffer. O(1)
Return Value: -
Reviewer = Benjamin.
*************/

void CBufferDestroy(cbuffer_t *c_buffer);

/*****************************************************************************
*Decription: Writes data (bytes) up to size of 'count', from 'src' to 'c_buffer'. O(n)
*Return Value: Quantity of bytes written. If 'count' is bigger then free space, copy up until reaches free space.
free space. -1 if failed.
Reviewer = Zeyad
*************/

ssize_t CBufferWrite(cbuffer_t *c_buffer, const void *src, size_t count);

/*****************************************************************************
*Decription: Read data (bytes) up to size of 'count', from 'c_buffer' to 'dest'.
O(n)
*Return Value: Number of bytes read. If 'count' is bigger then size, read up until size. -1 if Failed.
Reviewer = Zeyad
*************/

ssize_t CBufferRead(cbuffer_t *c_buffer, void *dest, size_t count);

/*****************************************************************************
Decription: Checks if 'c_buffer' is empty. O(1)
Return Value: 1 if is empty, 0 if is not empty.
Reviewer = Benjamin.
*************/

int CBufferIsEmpty(const cbuffer_t *c_buffer);

/*****************************************************************************
Decription: Checks size of c_buffer's buffer (array). O(1)
Return Value: Size of buffer, i.e how many bytes are already.
Reviewer = Benjamin.
*************/

size_t CBufferSize(const cbuffer_t *c_buffer);

/*****************************************************************************
Decription: Checks how much free space there is in the buffer. O(1)
Return Value: 0 if no free space.
Reviewer = Benjamin.
*************/

size_t CBufferFreeSpace(const cbuffer_t *c_buffer);

#endif /*__OL99_CBUFFER_H__ */





