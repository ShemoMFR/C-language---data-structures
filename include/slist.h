/******************************************************************************************
*Title: Linked List
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#ifndef __OL99_SLIST_H__
#define __OL99_SLIST_H__

typedef struct slist_node slist_node_t; 
typedef struct slist slist_t; 
typedef slist_node_t* slist_iter_t;
/*********************function************************/
/*
Decription: 	Create new linked list O(1)
Output:	pointer to a new linked list, returns NULL if fails
Reviewer : Benjamin
*/
slist_t *SListCreate(void);
/*****************************************************************************/
/*
Decription: 	Deletes linked list and frees all allocations O(n)
Reviewer : Benjamin
*/
void SListDestroy(slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Returns iterator to the beginning of linked list O(1)
Reviewer : Jake
*/

slist_iter_t SListBegin(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Returns iterator to the end of the linked list O(1)
Reviewer : Benjamin
*/
slist_iter_t SListEnd(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	returns iterator to next element O(1)
Reviewer : Benjamin
*/
slist_iter_t SListNext(const slist_iter_t iter); 
/*****************************************************************************/
/*
Decription: 	Compares two iterators O(1)	
Output:			1 if iterators are the same, 0  if different
Reviewer : Benjamin
*/            
int SListIsSameIterator(const slist_iter_t iter1 ,const slist_iter_t iter2);
/*****************************************************************************/
/*
Decription: 	returns data from node of linked list	O(1)
Reviewer : Benjamin
*/
void *SListGetData(const slist_iter_t iter);
/*****************************************************************************/
/*
Decription: 	Assigns data to a node O(1)
Reviewer : Benjamin
*/
void SListSetData(slist_iter_t iter, void *data);
/*****************************************************************************/
/*
Decription: 	Inserts a node into the linked list	O(1)
If failed, returns iter to the last node
Reviewer : Benjamin
*/

slist_iter_t SListInsert(slist_iter_t where, void *data);
/*****************************************************************************/
/*
Decription: 	Removes a node from the linked list	O(1)
returns iter to next node after the one removed
Reviewer : Jake
*/
slist_iter_t SListRemove(slist_iter_t iter);
/*****************************************************************************/
/*
Decription: 	Returns size of the linked list O(n) 
Reviewer : Zeyad
*/
size_t SListSize(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Checks if linked list is empty	O(1)
returns 1 if linked list is empty, other value if not
Reviewer : Jake
*/
int SListIsEmpty(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Searches linked list in specific range for requested element	
if found retruns iter to found element, if not returns iter to
Reviewer : Tsivia
*/
slist_iter_t SListFind(
    slist_iter_t from,
    slist_iter_t to,
    int (*is_match)(const void *data, void *param),
    void *param
);
/*
Decription: 	Applies user defined function to a range of elements	
returns output/status of action function
Reviewer : Zeyad
*/
int SListForEach(
    slist_iter_t from,
    slist_iter_t to,
    int (*action)(void *data, void *param),
    void *param
    );

/*
Decription: 	Append two Append two list. The first list will hold every nodes and 
the second list will be empty but with valide dummy tail. together O(1)
Reviewer : 
*/

void SListAppend(slist_t *dest, slist_t *src);

#endif /* __OL99_SLIST_H__ */










