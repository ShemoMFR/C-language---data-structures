/******************************************************************************************
*Title: sorted_list.c
*Author: Benjamin Bitton
*Last Reviewer: Tsivia 
*Description:
*Status: Approved
*****************************************************************************************/

#include <assert.h>		 /* assert */
#include <stdlib.h>		 /* malloc, free */

#include "dlist.h"		 
#include "sorted_list.h"

struct sorted_list
{
	dlist_t *list;
	int (*compare)(const void *lhs, const void *rhs);
};
/*
struct sorted_list_iter
{
	#ifndef NDEBUG
    sorted_list_t *sorted_list;
	#endif

    dlist_iter_t iterator;
};
*/
#define IF_DEBUG(list_iter) ((list_iter.sorted_list) = ((sorted_list_t *)list))
#define UNUSED(x) (void)(x)
#define SOL_ITER_TO_DL_ITER(iter) (iter.iterator)
#define SOL_ITER_TO_DLIST(iter) (iter.sorted_list)
/*********************functions************************/
/* Reviewer: Jane */
sorted_list_t *SoListCreate(int (*compare)(const void *data1, const void *data2))
{
	sorted_list_t *new_list = NULL;

	assert(compare);

	new_list = malloc(sizeof(sorted_list_t));
	if (NULL == new_list)
	{
		return NULL;
	}

	new_list->list = DListCreate();
	if (NULL == new_list->list)
	{
		free(new_list);
		return NULL;
	}

	new_list->compare = compare;

	return new_list;
}

/* Reviewer: Jane */
void SoListDestroy(sorted_list_t *list)
{
	assert(NULL != list);

	DListDestroy(list->list);
	list->compare = NULL;	
	list->list = NULL;

	free(list);
	list = NULL;
}

/* Reviewer: Jane */
sorted_list_iter_t SoListInsert(sorted_list_t *list, void *data)
{

	sorted_list_iter_t current = {NULL};

	assert(list);

	current = SoListBegin(list);

#ifndef NDEBUG
		SOL_ITER_TO_DLIST(current) = list;
#endif

	for (; !SoListIsSameIterator(current, SoListEnd(list))
			&& 0 > list->compare(SoListGetData(current), data);
			current = SoListNext(current));

	SOL_ITER_TO_DL_ITER(current) = DListInsert(SOL_ITER_TO_DL_ITER(current),
		   															data);
	return current;
}

/* Reviewer: Tsivia */
sorted_list_iter_t SoListRemove(sorted_list_iter_t which)
{
	sorted_list_iter_t iter_next = {0};
	
	assert(!SoListIsSameIterator(which, iter_next));

	SOL_ITER_TO_DL_ITER(iter_next) = DListRemove(SOL_ITER_TO_DL_ITER(which));

#ifndef NDEBUG
	SOL_ITER_TO_DLIST(iter_next) = SOL_ITER_TO_DLIST(which);
	SOL_ITER_TO_DLIST(which) = NULL;
#endif
	
	return iter_next;
}

/* Reviewer: Jane */
void *SoListPopFront(sorted_list_t *list)
{
	assert(list);

    return DListPopFront(list->list);
}

/* Reviewer: Jane */
void *SoListPopBack(sorted_list_t *list)
{
	assert(list);

    return DListPopBack(list->list);
}

/* Reviewer: Jane */
sorted_list_iter_t SoListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t begin = {0};
	
	assert(list);
#ifndef NDEBUG	
	IF_DEBUG(begin);
#endif	
	SOL_ITER_TO_DL_ITER(begin) = DListBegin(list->list);
	
	return begin;
}


/* Reviewer: Jane */
sorted_list_iter_t SoListEnd(const sorted_list_t *list)
{	
	sorted_list_iter_t end = {0};
	
	assert(list);
	
#ifndef NDEBUG
	IF_DEBUG(end);
#endif
	
	
	SOL_ITER_TO_DL_ITER(end) = DListEnd(list->list);

	return end;
}


/* Reviewer: Jane */
sorted_list_iter_t SoListNext(sorted_list_iter_t iterator)
{
	sorted_list_iter_t null_iter = {0};
	
	assert(!SoListIsSameIterator(iterator, null_iter));
	UNUSED(null_iter);
	
	SOL_ITER_TO_DL_ITER(iterator) = DListNext(SOL_ITER_TO_DL_ITER(iterator)); 
	
	return iterator;
}


/* Reviewer: Jane */
sorted_list_iter_t SoListPrev(sorted_list_iter_t iterator)
{
	sorted_list_iter_t null_iter = {0};
	
	assert(!SoListIsSameIterator(iterator, null_iter));
	UNUSED(null_iter);
	
	SOL_ITER_TO_DL_ITER(iterator) = DListPrev(SOL_ITER_TO_DL_ITER(iterator));
	
	return iterator;
}

/* Reviewer: Jane */
int SoListIsSameIterator(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{	
	int is_success = 1;
		
#ifndef NDEBUG
    is_success = is_success &&
	   	(SOL_ITER_TO_DLIST(iter1) == SOL_ITER_TO_DLIST(iter2));
#endif
	
	is_success = is_success && 
					DListIsSameIterator(SOL_ITER_TO_DL_ITER(iter1), 
							SOL_ITER_TO_DL_ITER(iter2));
	
	return is_success;
}


/* Reviewer: Jane */
void *SoListGetData(sorted_list_iter_t iterator)
{
	sorted_list_iter_t null_iter = {0};
	
	assert(!SoListIsSameIterator(iterator, null_iter));
	UNUSED(null_iter);

	return DListGetData(SOL_ITER_TO_DL_ITER(iterator));
}

/* Reviewer: Jane */
size_t SoListSize(const sorted_list_t *list)
{
	assert(list);

    return DListSize(list->list);
}

/* Reviewer: Jane */
int SoListIsEmpty(const sorted_list_t *list)
{
	assert(list);

	return DListIsEmpty(list->list);
}


/* Reviewer: Tsivia */
int SoListForEach(
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    int (*action)(void *data, void *param),
    void *param)
{
	assert(action);
	assert(SOL_ITER_TO_DL_ITER(from));
	assert(SOL_ITER_TO_DL_ITER(to));


    return DListForEach(
            SOL_ITER_TO_DL_ITER(from), 
            SOL_ITER_TO_DL_ITER(to),
            action,
            param);
}

/* Reviewer: Tsivia */
sorted_list_iter_t SoListFindIf(
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    int (*is_match)(const void *list_data, void *param),
    void *param)
{
	sorted_list_iter_t null_iter = {0};
	sorted_list_iter_t find = {0};

	assert(!SoListIsSameIterator(from, null_iter));
	assert(!SoListIsSameIterator(to, null_iter));
	assert(is_match);
	UNUSED(null_iter);

#ifndef NDEBUG
	SOL_ITER_TO_DLIST(find) = SOL_ITER_TO_DLIST(from);
#endif

	SOL_ITER_TO_DL_ITER(find) = 	DListFind(
                            SOL_ITER_TO_DL_ITER(from),
                            SOL_ITER_TO_DL_ITER(to),
                            is_match,
                            param);

	return find;
}

/* Reviewer: Tsivia */
sorted_list_iter_t SoListFind(
    sorted_list_t *solist,
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    void *to_find)
{
	
	sorted_list_iter_t null_iter = {0};

	assert(solist);
	assert(!SoListIsSameIterator(from, null_iter));
	assert(!SoListIsSameIterator(to, null_iter));
	UNUSED(null_iter);		

    for (; !SoListIsSameIterator(from, to) &&
            0 > solist->compare(SoListGetData(from),to_find);
            from = SoListNext(from));
    
    if (!SoListIsSameIterator(from, to) &&
		   	0 != solist->compare(SoListGetData(from),to_find))
    {
        return to;
    }

    return from;
}


/* Reviewer: Tsivia */
void SoListMerge(sorted_list_t *dest, sorted_list_t *src)
{
    sorted_list_iter_t where = {0};
    sorted_list_iter_t to = {0};
    sorted_list_iter_t end_dest = {0};
    sorted_list_iter_t end_src = {0};
	
	assert(dest);
	assert(src);

    where = SoListBegin(dest);
    to = SoListBegin(src);
    end_dest = SoListEnd(dest);
    end_src = SoListEnd(src);
	
    #ifndef NDEBUG
	    where.sorted_list = dest;
        to.sorted_list = src;
	#endif

    while (!SoListIsSameIterator(to, end_src))
    {
        sorted_list_iter_t from = to;
		/*iterating until where (dest) matches to (src) */
        for (;!SoListIsSameIterator(where, end_dest) && 
              0 > dest->compare(SoListGetData(where), SoListGetData(to)); 
              where = SoListNext(where));

        if (SoListIsSameIterator(where, end_dest))
        {
            DListSplice(SOL_ITER_TO_DL_ITER(SoListBegin(src)),
				   	SOL_ITER_TO_DL_ITER(SoListEnd(src)),
				   	SOL_ITER_TO_DL_ITER(where));
            break;
        }
		
        for (; !SoListIsSameIterator(to, end_src) && 
               0 >= dest->compare(SoListGetData(to), SoListGetData(where)); 
               to = SoListNext(to));
        
        DListSplice(SOL_ITER_TO_DL_ITER(from), SOL_ITER_TO_DL_ITER(to),
			   	SOL_ITER_TO_DL_ITER(where));
	}
}


















