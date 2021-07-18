/******************************************************************************************
*Title: Linked List_ex
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

enum end_prog
{
	SUCCESS = 0, FAILED = 1
};

typedef struct node
{
	void *data;
	struct node *next;
	
}node_t;

static void PrintList(node_t *head);
static int HasLoop(const node_t *head);
node_t *CreateNode(void *data);
node_t *Flip(node_t *head);
void TestList1();
void TestList2();
void FreeList(node_t *head);
void RemoveLoop(node_t *loop_node, node_t *head);
int CountLengList(node_t *head);
node_t *Intersection(node_t *small_iter, node_t *big_iter, int diff);
void TestLoop(int ValLoop, node_t *head);
int TestDiff(int diff1, int diff2, node_t *head, node_t *head2);

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

int main(void)
{
	TestList1();
	TestList2();
	
	return SUCCESS;	
}

void TestList1()
{
/************************ INIT VALUES ************************/		

	int val1 = 10;
	int val2 = 20;
	int val3 = 30;
	int val4 = 40;	
	int val5 = 50;
	int IsLoop = 0;
	
	node_t *head = CreateNode(&val1);
	node_t *node2 = CreateNode(&val2);
	node_t *node3 = CreateNode(&val3);
	node_t *node4 = CreateNode(&val4);
	node_t *node5 = CreateNode(&val5);
	
	head->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;;
	node5->next = node4;
	
/************************ TEST1 PART ************************/		
	printf(""KBLU"******************* TEST SINGLY LIST ******************"KNRM"\n\n");
	IsLoop = HasLoop(head);	
	TestLoop(IsLoop, head);	
	head = Flip(head);
	printf(""KBLU"FLIP : "KNRM"");
	PrintList(head);		
	FreeList(head); 
}

void TestList2()
{
	int val1 = 10;
	int val2 = 20;
	int val3 = 30;
	int val4 = 40;	
	int val5 = 50;
	int diff_leng1 = 0;
	int diff_leng2 = 0;
	int diff = 0;
	
/************************** list1 **********************/	

	node_t *head = CreateNode(&val1);
	node_t *node2 = CreateNode(&val2);
	node_t *node3 = CreateNode(&val3);
	node_t *node4 = CreateNode(&val4);
	node_t *node5 = CreateNode(&val5);
	node_t *iter_intersection = NULL;
	
/************************ list2 ************************/		
	
	node_t *head2 = CreateNode(&val3);
	node_t *node6 = CreateNode(&val2);
	node_t *node7 = CreateNode(&val1);
	node_t *node8 = CreateNode(&val5);
	
	head->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;;
	node5->next = NULL;
	
	head2->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = node4;

/************ Test leng + search intersection **********/ 
	
	diff_leng1 = CountLengList(head);
	diff_leng2 = CountLengList(head2);
	diff = TestDiff(diff_leng1, diff_leng2, head, head2);	

	iter_intersection = Intersection(head, head2, diff);
	printf(""KGRN"SUCCESS"KNRM" Intersection found\n");
	
	FreeList(head);	
	free(node8);
	free(node7);
	free(node6);
	free(head2);
	printf(""KGRN"SUCCESS"KNRM" Every memory blocks are freed\n");
	
}

node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	
	assert(data);
	
	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}

node_t *Flip(node_t *head)
{
	node_t *current = head;
	node_t *prev = NULL;
	node_t *next = NULL;
	
	assert(head);
	
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	
	head = prev;
	
	return head;

}

static void PrintList(node_t *head)
{
	node_t *temp = head;
	
	assert(head);
	
    while (temp != NULL) 
    {
        printf("%d [->] ", *(int *)temp->data);
        temp = temp->next;
    }
    
    printf("NULL\n");

}

static int HasLoop(const node_t *head) /* equivalent to (N-L)%L give us the distance between both pointers */
{
	const node_t *cursor1 = NULL;
	const node_t *cursor2 = NULL;
	
	assert(head);
	
	cursor1 = head;
	cursor2 = head->next;
	
	while (cursor1->next && cursor2->next)
	{
		if (cursor1 == cursor2)
		{
			RemoveLoop((node_t *)cursor2, (node_t *)cursor1);
			return 1;
		}
		else
		{
			cursor1 = cursor1->next;
			cursor2 = cursor2->next->next;
		}
	}
	
	return 0;
}

void FreeList(node_t *head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

void TestLoop(int ValLoop, node_t *head)
{
	if (1 == ValLoop)
	{
		printf(""KRED"THE LIST HAS LOOP"KNRM" \n");
		printf(""KGRN"SUCCES"KNRM" Loop removed \n");
		printf(""KBLU"INIT : "KNRM"");
		PrintList(head);
	}
	else
	{
		printf(""KBLU"THE LIST DOES NOT HAVE LOOP"KNRM" \n");
		printf(""KBLU"INIT : "KNRM"");
		PrintList(head);
	}

}

void RemoveLoop(node_t *loop_node, node_t *head)
{
	node_t *ptr1 = head;
	node_t *ptr2 = loop_node;
	
	if (NULL != ptr1)
	{
		while (ptr1->next != head) 
		{
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		
		ptr2->next = NULL;
	}
}

int CountLengList(node_t *head)
{
	node_t *tmp = head;
	int count = 0;
		
	while (tmp != NULL)
	{
		++count;
		tmp = tmp->next;
	}
	
	return count;
}

node_t *Intersection(node_t *small_iter, node_t *big_iter, int diff)
{
	node_t *tmp = small_iter;
	node_t *tmp2 = big_iter;
	int i = 0;
	
	for (; i < diff; i++)
	{
		tmp2 = tmp2->next;
	}
	
	while (tmp != tmp2)
	{
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}

	return tmp;
}

int TestDiff(int diff1, int diff2, node_t *head, node_t *head2)
{
	if (CountLengList(head) < CountLengList(head2))
	{
		return CountLengList(head2) - CountLengList(head);
	}	
	else
	{
		return CountLengList(head) - CountLengList(head2);
	}
}




















