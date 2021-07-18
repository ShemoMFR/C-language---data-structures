/******************************************************************************************
*Title: tree
*Author : 
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdlib.h> /* malloc / free*/ 
#include <stdio.h> /* prinf=tf */
#include <assert.h> /* assert */
#include "tree.h" 

node_t *CreateNode(unsigned int item);

struct node
{
    unsigned int key;
    struct node *left;
    struct node *right;
};

node_t *CreateNode(unsigned int item) 
{ 
    node_t *temp = (node_t *)malloc(sizeof(node_t)); 
    temp->key = item; 
    temp->left = NULL;
    temp->right = NULL;
     
    return temp; 
} 

node_t *BstInsert(node_t *node, unsigned int key) 
{ 		
    if (NULL == node) 
    {
        return CreateNode(key); 
    }
  
    if (key < node->key) 
    {
        node->left = BstInsert(node->left, key); 
    }
    else if (key > node->key) 
    {
        node->right = BstInsert(node->right, key); 
    }
  
    return node; 
} 

/*void BstPrintInOrder(node_t *root)
{ 
	
    if (NULL != root) 
    { 
        BstPrintInOrder(root->left); 
        printf("%d \n", root->key); 
        BstPrintInOrder(root->right); 
    } 
} */

void BstPrintInOrder(node_t *root, int niveau)
{
	int i;
	
	if (NULL != root)
	{
		for(i=0; i<niveau; i++) 
		printf("%5s"," ");
		printf("%d\n",root->key);
		BstPrintInOrder(root->left, niveau+1);
		BstPrintInOrder(root->right, niveau+1);
	}

}

int BstSearchNumber(node_t *root, int nbr)
{
    node_t *tmp = root;
    
    if (IsEmpty(root))
    {
    	return 0;
    }
     
    while (tmp->key != nbr && NULL != tmp)
    {
        if (nbr < tmp->key)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }  
    }
     
    return (tmp->key == nbr);
 
}

void BstDelete(node_t *root)
{
	node_t *tmp = root;
		
	if (NULL != root)
	{	
		BstDelete(root->left);
		root->left = NULL;
		BstDelete(root->right);
		root->right = NULL;
		free(root);
		root = NULL;
	}
}

int IsEmpty(node_t *root)
{
	return (NULL == root->left && NULL == root->right);
}









