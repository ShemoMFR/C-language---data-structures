/******************************************************************************************
*Title:queue.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h>

#include "queue.h" 
#include "slist.h" 

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

static void TestQueue();
static void IntCompare(int input, int output, char *Test);

enum end_prog
{
	SUCCESS = 0, FAILEd = 1
};

int main(void)
{
	TestQueue();

	return SUCCESS;
}

static void TestQueue()
{
	int val1 = 10;
	int val2 = 20;
	int val3 = 25;
	int val4 = 15;
	int result = 1;
	int empty = 0;
	int *insert1 = NULL;
	size_t size = 0;
	queue_t *new_queue2 = NULL;

/*******************Create*********************/	
	
	queue_t *new_queue = QCreate();
			
/*****************Is Empty*********************/

	printf(""KBLU"************** TEST ISEMPTY *********************"KNRM"\n");		
	empty = QIsEmpty(new_queue);
	IntCompare(empty, 1, "Empty");
	
/***************Insert 1 Item******************/
	printf(""KBLU"************** TEST INSERT *********************"KNRM"\n");		
	result = QEnqueue(new_queue, &val1);
	IntCompare(result, 1, "Insert");	
	size = QSize(new_queue);
	IntCompare(size, 1, "Size");
	
/**************Check its value*****************/
	printf(""KBLU"************** TEST PEEK *********************"KNRM"\n");		
	insert1 = QPeek(new_queue);
	IntCompare(*insert1, val1, "Peek and Insert");

/*****************Not Empty****************/
	printf(""KBLU"************** TEST ISEMPTY *********************"KNRM"\n");		
	empty = QIsEmpty(new_queue);
	IntCompare(empty, 0, "Not Empty");
	
/****************Remove Value******************/
	printf(""KBLU"************** TEST REMOVE VALUE ****************"KNRM"\n");		
	QDequeue(new_queue);
	empty = QIsEmpty(new_queue);
	IntCompare(empty, 1, "Remove");
	
/***************Insert 2 Val*******************/
	printf(""KBLU"************** TEST INSERT *********************"KNRM"\n");		
	result = QEnqueue(new_queue, &val1);	
	result = QEnqueue(new_queue, &val2);	
	size = QSize(new_queue);
	IntCompare(size, 2, "Size");

/*****************Queue Append******************/
	printf(""KBLU"************** TEST APPEND *********************"KNRM"\n");		
	new_queue2 = QCreate();
	result = QEnqueue(new_queue2, &val3);
	result = QEnqueue(new_queue2, &val4);
	size = QSize(new_queue2);
	IntCompare(size, 2, "New Queue Size Pre-Append");
	QAppend(new_queue, new_queue2);
	size = QSize(new_queue);
	IntCompare(size, 4, "Queue Size Post-Append");
	empty = QIsEmpty(new_queue2);
	IntCompare(empty, 1, "Empty Append");
	
	QDestroy(new_queue);
	QDestroy(new_queue2);


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



