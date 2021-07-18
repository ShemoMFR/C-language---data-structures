/******************************************************************************************
*Title: Linked List
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc/free */
#include "slist.h"

static slist_node_t *CreateNode();
int SListForEach(slist_iter_t from, slist_iter_t to, int (*is_match)(void *data, void *param),void *param);
static int action(void *data, void *param);
void SwitchNodes(slist_iter_t iter1, slist_iter_t iter2);

struct slist_node
{
	void *data;
	struct slist_node *next;
};

struct slist
{
 	slist_node_t *head;
	slist_node_t *tail;
};

enum is_bool
{
	FALSE = 0, TRUE = 1
};

slist_t *SListCreate(void)
{
	slist_t *new_slist = (slist_t *)malloc(sizeof(slist_t));
	slist_node_t *dummy_tail = CreateNode();
	
	if (new_slist == NULL)
	{
		free(dummy_tail);
		dummy_tail = NULL;
		return new_slist;
	}
	
	if (dummy_tail == NULL)
	{
		free(new_slist);
		new_slist = NULL;
		return NULL;
	}
		
    new_slist->head = dummy_tail;
    new_slist->tail = dummy_tail;
    dummy_tail->data = new_slist;
    dummy_tail->next = NULL;
    
    return new_slist;
}

void SListDestroy(slist_t *slist)
{
    
    slist_iter_t iter = NULL;

    assert(slist);
    
    iter = SListBegin(slist);
    
    while(!SListIsSameIterator(iter, SListEnd(slist)))
    {    
        iter = SListRemove(iter);
    }
    
    free(iter);
    iter = NULL;
    slist->head = NULL;
    slist->tail = NULL;
    free(slist);
    slist = NULL;    
}

slist_iter_t SListRemove(slist_iter_t iter)
{
    slist_iter_t to_free = iter->next;
    iter->data = iter->next->data;
    iter->next = iter->next->next;
    
    assert(iter);
    free(to_free);
    
    if (NULL == iter->next)
    {
        ((slist_t *)iter->data)->tail = iter; 
    }
    return iter;
}


slist_node_t *CreateNode()
{
    slist_node_t *ptr = (slist_node_t *)malloc(sizeof(slist_node_t));        
    return ptr;
}

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(slist);
	return slist->head;
}

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(slist);
	return slist->tail;
}

slist_iter_t SListNext(const slist_iter_t iter)
{
	assert(iter);
	return iter->next;
}

int SListIsEmpty(const slist_t *slist)
{
	assert(slist);
	return (slist->head->next == NULL);
}

void *SListGetData(const slist_iter_t iter)
{
	assert(iter);
	return iter->data;
}

void SListSetData(slist_iter_t iter, void *data)
{
	assert(iter);
	assert(data);
	iter->data = data;
}

int SListIsSameIterator(const slist_iter_t iter1 ,const slist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	return (iter1 == iter2);
}

size_t SListSize(const slist_t *slist)
{
	size_t count = 0;
	
	assert(slist);
	
	SListForEach(SListBegin(slist), SListEnd(slist), action, &count);
	
	return count;
}

slist_iter_t SListInsert(slist_iter_t where, void *data)
{
	slist_t *list = NULL;
	slist_iter_t newNode = CreateNode();
	
	assert(where);
	assert(data);

	if (NULL == newNode)
	{
		while (NULL != SListNext(where))
		{
			where = SListNext(where);
		}	
		return where;
	}
	
	newNode->data = where->data;
	newNode->next = where->next;
	where->next = newNode;
	where->data = data;
	
	if (NULL == newNode->next)
	{
		list = newNode->data;
		list->tail = newNode;
	}
	
	return newNode;	
}

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, int (*is_match)(const void *data, void *param),void *param)
{
	slist_iter_t tmp = from;
	
	assert(param);
	assert(from);
	assert(to);
	
	while (!SListIsSameIterator(tmp, to))	
	{	
		if (TRUE == is_match(tmp->data, param))
		{
			return tmp;
		}
		tmp = SListNext(tmp); 
	}

	return to;
}

int SListForEach(slist_iter_t from, slist_iter_t to, int (*is_match)(void *data, void *param),void *param)
{
	slist_iter_t tmp = from;
	int result = 0;

	assert(param);
	assert(from);
	assert(to);
	
	for (;!SListIsSameIterator(tmp, to); tmp = SListNext(tmp))
	{
		result = action(SListGetData(from), param);
	}
	
	return result;
}

static int action(void *data, void *param)
{
	(void)data;
	assert(param);
	
	return (*(size_t *)param += 1);   
}

void SListAppend(slist_t *dest, slist_t *src)
{
	assert(dest);
	assert(src);
	
	if (!SListIsEmpty(dest) &&  !SListIsEmpty(src))
	{	
    	slist_node_t *dummyTailTo = SListEnd(dest);
    	slist_node_t *dummyTailFrom = SListEnd(src);
    
    	slist_node_t *headSrc = SListBegin(src);
    
    	dummyTailTo->data = headSrc->data;
    	dummyTailTo->next = headSrc->next;
    
    	dummyTailFrom->data = (void*)dest;
    	dest->tail = dummyTailFrom;
 
    	headSrc->data = src;
    	headSrc->next = NULL;
    	src->tail = headSrc; 
    }
}
















