/******************************************************************************************
*Title:queue
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "queue.h" 
#include "slist.h" 

 struct queue
 {
 	slist_t *list;
 };

queue_t *QCreate(void)
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
		
	if (new_queue == NULL)
	{
		return new_queue;
	}
	
	new_queue->list = SListCreate();
	
	return new_queue;
}

void QDestroy(queue_t *queue)
{
	assert(queue);
	SListDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	queue = NULL;
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(queue);
	assert(data);
	
	SListInsert(SListEnd(queue->list), data);
	
	return !(QIsEmpty((queue_t *)queue->list)); /* if begin == end, the list is empty and return 0, if 1 the list not empty and Insert woroked*/
}

void *QPeek(const queue_t *queue)
{
	assert(queue);
	return SListGetData(SListBegin(queue->list));
}

void QDequeue(queue_t *queue)
{
	assert(queue);
	
	if (!(SListBegin(queue->list) == SListEnd(queue->list)))
	{
		SListRemove(SListBegin(queue->list));
	}
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return (SListIsEmpty(queue->list));
}

size_t QSize(const queue_t *queue)
{
	assert(queue);
	return SListSize(queue->list);
}

void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	SListAppend(dest->list, src->list);
}

























