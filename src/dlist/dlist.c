/******************************************************************************************
*Title: dlist.h
*Author : Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdlib.h> /* malloc/free */
#include <assert.h> /* assert */
#include "dlist.h"

static int action(void *data, void *param);

dlist_node_t *CreateNode();

struct dlist_node
{
    void *data;
    struct dlist_node *next;
    struct dlist_node *prev;
};

struct dlist
{    
    dlist_node_t head;
    dlist_node_t tail;
};

dlist_t *DListCreate(void)
{
    dlist_t *new_dlist = (dlist_t *)malloc(sizeof(dlist_t));
    
    if (NULL == new_dlist)
    {
        return new_dlist;    
    }
    
    new_dlist->head.data = NULL;
    new_dlist->head.prev = NULL;
    new_dlist->head.next = &(new_dlist->tail);
       
    new_dlist->tail.data = NULL;
    new_dlist->tail.prev = &(new_dlist->head);
    new_dlist->tail.next = NULL;

    return new_dlist;

}

void DListDestroy(dlist_t *list)
{
	dlist_iter_t iter = {0};
	dlist_iter_t iter_end = {0};

	assert(list);
	
	iter = DListBegin(list);
	iter_end = DListEnd(list);
	
	while(!DListIsSameIterator(iter, iter_end))
	{
		iter = DListRemove(iter);
	}

	list->head.data = NULL;
	list->head.prev = NULL;
	list->head.next = NULL;
	
	list->tail.data = NULL;
	list->tail.prev = NULL;
	list->tail.next = NULL;
	
	free(list);
	list = NULL;
}

dlist_iter_t DListRemove(dlist_iter_t who)
{
	dlist_iter_t current = NULL;
	dlist_iter_t prev = NULL;
    
	assert(who);
	assert(who->next);
	
	current = DListNext(who);
	prev = DListPrev(who);
        
    prev->next = current;

    free(who);
    who = NULL;

    return current;
}

dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
	dlist_iter_t new_node = CreateNode();
	
	assert(where);
	assert(data);
	
	if (NULL == new_node)
	{
		while (NULL != DListNext(where))
		{
			where = DListNext(where);
		}	
		return where;
	}
	
	new_node->prev = where->prev;
	new_node->next = where;
	where->prev->next = new_node;	
	where->prev = new_node;
	new_node->data = data;

	return new_node;
}

dlist_node_t *CreateNode()
{
    dlist_node_t *new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));        
    return new_node;
}

dlist_iter_t DListBegin(const dlist_t *list)
{
	assert(list);
	return (dlist_iter_t)list->head.next;
}

dlist_iter_t DListEnd(const dlist_t *list)
{
	assert(list);
	return (dlist_iter_t)&(list->tail);
}

dlist_iter_t DListNext(dlist_iter_t iterator)
{
	assert(iterator);
	return iterator->next;
}

dlist_iter_t DListPrev(dlist_iter_t iterator)
{
	return iterator->prev;
}


int DListIsSameIterator(dlist_iter_t iter1, dlist_iter_t iter2)
{
	return (iter1 == iter2);
}

int DListIsEmpty(const dlist_t *list)
{
	assert(list);
	return (DListIsSameIterator(DListBegin(list), DListEnd(list)));
}

size_t DListSize(const dlist_t *list)
{
	size_t count = 0;
	
	assert(list);
	
	DListForEach(DListBegin(list), DListEnd(list), action, &count);
	
	return count;
}

void *DListGetData(dlist_iter_t iterator)
{
	assert(iterator);
	return iterator->data;
}

void DListSetData(dlist_iter_t iterator, void *data)
{
	assert(iterator);
	assert(data);
	
	iterator->data = data;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, int (*is_match)(void *data, void *param),void *param)
{
	dlist_iter_t tmp = from;
	int result = 0;

	assert(param);
	assert(from);
	assert(to);
	
	for (;!DListIsSameIterator(tmp, to); tmp = DListNext(tmp))
	{
		result = action(DListGetData(from), param);
	}
	
	return result;
}

static int action(void *data, void *param)
{
	(void)data;
	assert(param);
	
	return (*(size_t *)param += 1);   
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, int (*is_match)(const void *data, void *param),void *param)
{
	dlist_iter_t tmp = from;
	
	assert(param);
	assert(from);
	assert(to);
	
	while (!DListIsSameIterator(tmp, to))	
	{	
		if (1 == is_match(tmp->data, param))
		{
			return tmp;
		}
		tmp = DListNext(tmp); 
	}

	return to;
}









