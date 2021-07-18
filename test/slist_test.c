/******************************************************************************************
*Title: Linked List
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "slist.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

static void TestList();
static void TestMergeLists();
int Is_Match_int(const void *data, void *param);
void TestIsEmpty(int IsEmpty);
void TestInitList(slist_t *list);
void TestSize(size_t val);
void TestSameIterator(int val);
void TestInsert(int *val, int val2);

enum end_prog
{
	SUCCESS = 0, FAILED = 1
};

int main(void)
{
	
	TestList();
	TestMergeLists();

	return SUCCESS;
}

void TestList()
{
/*********************** INITIALISATION LINKED LIST *********************************/

	int IsEmpty = 0;
	slist_t *new_slist = SListCreate();	
	int data1 = 10;
	int data3 = 30;
	size_t size_list = 0;
	int IsSameIt = 0;
	int *result = NULL;
	slist_iter_t test = 0;	
	
/*********************** INITIALISATION LINKED LIST *********************************/
	printf(""KBLU"************** TEST INIT LIST *********************"KNRM"\n");		
	TestInitList(new_slist);

/****************************** TEST LIST IS EMPTY *********************************/	
	printf(""KBLU"************** TEST EMPTY LIST *********************"KNRM"\n");	
	IsEmpty = SListIsEmpty(new_slist);
	
	TestIsEmpty(IsEmpty);
	
/****************************** TEST SIZE LIST *********************************/	
	printf(""KBLU"************** TEST SIZE LIST *********************"KNRM"\n");	
	size_list = SListSize(new_slist);
	
	TestSize(size_list);
			
/****************************** TEST SAME ITERATOR *********************************/	
	printf(""KBLU"************** TEST SAME ITERATOR *********************"KNRM"\n");	
	IsSameIt = SListIsSameIterator(SListBegin(new_slist), SListEnd(new_slist));
	
	TestSameIterator(IsSameIt);
		
/****************************** TEST INSERT DATA *********************************/	
	printf(""KBLU"************** TEST INSERT DATA*********************"KNRM"\n");	
	SListInsert(SListBegin(new_slist), &data1);
	result = SListGetData(SListBegin(new_slist));
	
	TestInsert(result, data1);	 
	SListInsert(SListNext(SListBegin(new_slist)), &data3);

	
/****************************** TEST GET DATA *********************************/	
	printf(""KBLU"************** TEST GET DATA*********************"KNRM"\n");
	SListSetData(SListBegin(new_slist), &data3);
	result = SListGetData(SListBegin(new_slist));
	
	if (*result == 30)
	{
		printf(""KGRN"SUCCES"KNRM" value changed\n");
	}
	else
	{
		printf(""KRED"ERROR"KNRM" With the changing value\n");
	}

/****************************** TEST ISFOUND DATA *********************************/	
	printf(""KBLU"************** TEST ISFOUND DATA*********************"KNRM"\n");	
	
	SListEnd(new_slist);
	test = SListFind(SListBegin(new_slist), SListEnd(new_slist), Is_Match_int, &data3);
	
	if (test == SListBegin(new_slist))
	{
		printf(""KGRN"SUCCES"KNRM" value matched\n");
	}	
	else
	{
		printf(""KRED"ERROR"KNRM" value matched\n");
	}
	
	
/****************************** TEST INSERT DATA *********************************/	
	printf(""KBLU"************** TEST DESTROY DATA*********************"KNRM"\n");		
		
	SListDestroy(new_slist);
	printf(""KGRN"SUCCES"KNRM" List deleted and removed\n");	
}

int Is_Match_int(const void *data, void *param)
{
	return (*(int *)data == *(int *)param);	
}

void TestMergeLists()
{
	int data1 = 10;
	int data2 = 20;
	int *result;
	
	slist_iter_t iter = NULL;
	
	slist_t *slist1 = SListCreate();
	slist_t *slist2 = SListCreate();
	
	SListInsert(SListBegin(slist1), &data1);
	SListInsert(SListBegin(slist1), &data1);
	SListInsert(SListBegin(slist1), &data1);
	
	SListInsert(SListBegin(slist2), &data2);
	SListInsert(SListBegin(slist2), &data2);
	SListInsert(SListBegin(slist2), &data2);
	
/****************************** TEST INSERT DATA *********************************/		
	printf(""KBLU"************** TEST APPEND LIST*******************"KNRM"\n");			
	
	printf("Size list : %lu\n", SListSize(slist1));
	SListAppend(slist1, slist2);	
	printf("Size after append list : %lu\n", SListSize(slist1));
		printf("Size after append list : %lu\n", SListSize(slist2));
	
	if (1 == SListIsEmpty(slist2))
	{
		printf(""KGRN"SUCCES"KNRM" The list2 is empty now\n");
	}
	else
	{
		printf(""KRED"ERROR"KNRM" The list2 is not empty\n");
	}
	
	iter = SListBegin(slist1);
	iter = SListNext(iter); 
	iter = SListNext(iter); 
	iter = SListNext(iter); 
	
	result = SListGetData(iter);
	printf("%d\n", *result);
			
 	SListDestroy(slist1);
 	SListDestroy(slist2);
       
}

void TestIsEmpty(int IsEmpty)
{
	if (IsEmpty == 1)
	{
		printf(""KGRN"SUCCES"KNRM" The list is empty now\n");
	}
	else
	{
		printf(""KRED"ERROR"KNRM" With the function IsEmpty\n");
	}

}
void TestInitList(slist_t *list)
{
	if (list != NULL)
	{
		printf(""KGRN"SUCCES"KNRM" List Created\n");
	}
	else
	{
		printf(""KRED"ERROR"KNRM" List not created\n");
	}
}

void TestSize(size_t size)
{
	if (size != 0)
	{
		printf(""KRED"ERROR"KNRM" With the size of list\n");	
		printf("%lu", size);
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" The size of list is 0\n");
	}	
}

void TestSameIterator(int val)
{
	if (val == 1)
	{
		printf(""KGRN"SUCCES"KNRM" Is the same iterator\n");
	}
	else
	{
		printf(""KRED"ERROR"KNRM" With the function IsSameIt\n");
	}	
}

void TestInsert(int *val, int val2)
{
	if (*val != val2)
	{
		printf(""KRED"ERROR"KNRM" With the insert value\n");
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" insert value\n");
	}	
}	














