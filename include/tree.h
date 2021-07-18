/******************************************************************************************
*Title: tree
*Author : 
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#ifndef __TREE_BINARY_H__
#define __TREE_BINARY_H__

typedef struct node node_t;

#include <stddef.h> /* size_t, ssize_t */

/**************************************************************
Description : Insert node depend of the logic of the tree : if new key is less that the previous, insert left place. If bigger, right place.
return pointer to new node
Complexity : O(1) */

node_t *BstInsert(node_t *node, unsigned int key);

/*Description : Print in order all element of the tree
Complexity : O(n) */

void BstPrintInOrder(node_t *root, int niveau);

/*Description : Research number in the tree/
Return : 1 if found. 0 if not.
Complexity : O(n) */

int BstSearchNumber(node_t *root, int nbr);

/*Description : Delete all the nodes
Return : 
Complexity : O(log n) */

void BstDelete(node_t *root);

/*Description : Delete all the nodes
Return : 1 if Tree Is Empty, 0 if not.
Complexity : O(1) */

int IsEmpty(node_t *root);


#endif /*__TREE_BINARY_H__ */
