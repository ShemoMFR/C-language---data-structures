/******************************************************************************************
*Title: dlist.h
*Author : Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h>
#include "dlist.h" 

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

void TestDList();
static void IntCompare(int input, int output, char *Test);
int Is_Match_int(const void *data, void *param);

int main(void)
{
	TestDList();
		
	return 0;
}

void TestDList()
{
	dlist_t *new_list = DListCreate();
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int *result = NULL;
	dlist_iter_t test = NULL;
	dlist_iter_t iter = NULL;
	
/*****************Is Empty*********************/
	printf(""KBLU"************** TEST ISEMPTY *********************"KNRM"\n");	
	IntCompare(DListIsEmpty(new_list), 1, "IsEmpty");	
/*****************INSERT*********************/
	printf(""KBLU"************** TEST INSERT *********************"KNRM"\n");	
	iter = DListInsert(DListBegin(new_list), &data1);
	IntCompare(DListIsEmpty(new_list), 0, "Not Empty");
	iter = DListNext(iter);
	iter = DListInsert(iter, &data2);
	
/*****************GET DATA*********************/
	printf(""KBLU"************** TEST GET DATA *********************"KNRM"\n");	
	result = DListGetData(DListBegin(new_list));
	IntCompare(*result, 10, "Data node 1"); 
	result = DListGetData(iter);
	IntCompare(*result, 20, "Data node 2"); 
	
/*****************NEXT*********************/
	printf(""KBLU"************** TEST SET DATA *********************"KNRM"\n");	
	iter = DListInsert(DListEnd(new_list), &data3);
	result = DListGetData(iter);
	IntCompare(*result, 30, "Data node 3"); 
	
/*****************SIZE*********************/
	printf(""KBLU"************** TEST SIZE *********************"KNRM"\n");	
	IntCompare(DListSize(new_list), 3, "Size"); 
	
/*****************IS FOUND*********************/
	/*printf(""KBLU"************** TEST IS FOUND + IsSameIterator*********************"KNRM"\n");	
	
	test = DListFind(DListBegin(new_list), DListEnd(new_list), Is_Match_int, &data3);
	IntCompare(DListIsSameIterator(iter, test), 1, "IsFound"); 
	
	
	*/
	
	
	DListDestroy(new_list);

}

static void IntCompare(int input, int output, char *Test)
{
	if (input == output)
	{
		printf(""KGRN"SUCCES"KNRM" %s test : returned %d\n", Test, output); 
	}
	
	else
	{
		printf(""KRED"ERROR"KNRM" %s test : expected %d returned %d\n"KNRM, Test, output, input);
	}
} 

int Is_Match_int(const void *data, void *param)
{
	return (*(int *)data == *(int *)param);	
}



