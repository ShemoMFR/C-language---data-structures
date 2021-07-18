/*****************************************************************************
*Title: sorted_list.h
*Author: 
*Reviewer: 
*Description: Sorted Doubly Linked List
*Status: in developpment
******************************************************************************/

#ifndef __OL99_SORTEDLIST_H__
#define __OL99_SORTEDLIST_H__

#include <sys/types.h> /* size_t, ssize_t */
#include "dlist.h"

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iter sorted_list_iter_t;

struct sorted_list_iter
{
	#ifndef NDEBUG
    sorted_list_t *sorted_list;
	#endif

    dlist_iter_t iterator;
};

/*****************************************************************************/

/*
Decription: Create new Sorted doubly linked list, 
Returns a pointer to a manager object of a new double linked list, 
NULL if fail. O(1)
*/

sorted_list_t *SoListCreate(int (*compare)(const void *data1, const void *data2));

/*****************************************************************************/
/*
Decription: Destroys Sorted doubly linked list (free all allocations) O(n).	
*/

void SoListDestroy(sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Returns an iterator to the beginning of the list. O(1)
*/

sorted_list_iter_t SoListBegin(const sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Returns an iterator to the end of the list. O(1)
Returns iterator to the tail that is not a valid element.
*/
sorted_list_iter_t SoListEnd(const sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Returns an iterator to the next node. O(1)
*/
sorted_list_iter_t SoListNext(sorted_list_iter_t iterator);

/*****************************************************************************/
/*
Decription: Return an iterator to the previous node. O(1)
*/
sorted_list_iter_t SoListPrev(sorted_list_iter_t iterator);

/*****************************************************************************/
/*
Decription: Returns 1 if iterators are the same, 0 if different. O(1)
*/
int SoListIsSameIterator(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*****************************************************************************/
/*
Decription: Returns the data of node O(1)
*/
void *SoListGetData(sorted_list_iter_t iterator);

/*****************************************************************************/
/*
Decription: Inserts a node into the sorted doubly linked list, keeps it sorted. 
Returns iterator to inserted node. 
If failed, returns iterator to end of list. O(n)
*/

sorted_list_iter_t SoListInsert(sorted_list_t *list, void *data);

/*****************************************************************************/
/*
Decription: Removes a node from the sorted double linked list. O(1)
Returns iterator to next node.
*/
sorted_list_iter_t SoListRemove(sorted_list_iter_t which);

/*****************************************************************************/
/*
Decription: Returns size of the sorted double linked list O(n)
*/
size_t SoListSize(const sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Returns 1 if list is empty, 0 otherwise O(1)
*/
int SoListIsEmpty(const sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Delete a node in the beginning of the list O(1)
Returns the data of the popped node.
*/
void *SoListPopFront(sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Delete a node in the end of the list O(1)
Returns the data of the popped node.
*/
void *SoListPopBack(sorted_list_t *list);

/*****************************************************************************/
/*
Decription: Searches Sorted linked list in specific range for requested element	
Output: First found iterator to requested element. If not, iterator to "to".
O(n)
*/
sorted_list_iter_t SoListFind(
    sorted_list_t *solist,
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    void *to_find);

/*****************************************************************************/
/*
Decription: Searches Sorted linked list in specific range for requested element	
Output: First found iterator to requested element. If not, iterator to "to".
O(n)
*/
sorted_list_iter_t SoListFindIf(
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    int (*is_match)(const void *list_data, void *param),
    void *param);

/*****************************************************************************/
/*
Decription: Applies user defined function to a range of elements, returns 
return value of action function. O(n)
*/
int SoListForEach(
    sorted_list_iter_t from,
    sorted_list_iter_t to,
    int (*action)(void *data, void *param),
    void *param);

/*****************************************************************************/

/*
Decription: Adds elements from the src list to the dest list in an ordered way. 
O(n + m) Lists should have the same comparison function.

src list becomes empty but still valid.
*/

void SoListMerge(sorted_list_t *dest, sorted_list_t *src);



#endif /*__OL99_SORTEDLIST_H__ */



