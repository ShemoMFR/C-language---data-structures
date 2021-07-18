/*****************************************************************************
*Title: dvector.h 
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
******************************************************************************/
#include <stdio.h>
#include "dvector.h" 

enum end_process
{
	SUCCESS = 0, FAILED = 1, CHANGED = 2
};

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

void TestVector();

int main(void)
{
	TestVector();
	
	return SUCCESS;
}

void TestVector()
{
	int statut = 0;
	int statut2 = 0;
	int statut3 = 0; 
	size_t set = 15;
	size_t set2 = 9;
	size_t index10 = 10;
	size_t index15 = 15;

	vector_t *myvector = VectorCreate(20);
	
/*********************** INITIALISATION VECTOR ***************************************/
	printf(""KBLU"************** TEST INIT VECTOR*********************"KNRM"\n");
	printf("The vector is created with the capacity : 20\n");	

/************************** VECTOR CAPACITY ******************************************/
	printf(""KBLU"************** TEST CAPACITY*********************"KNRM"\n");
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	
/*********************** PUSH ELEMENT VECTOR *****************************************/	
	printf(""KBLU"************** TEST PUSH ELEMENT********************"KNRM"\n");
	statut2 = VectorPushBack(myvector, (void *)10);
	if(statut2 == FAILED)
	{
		printf(""KRED"ERROR"KNRM" Problem with the element pushed !\n");
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" Element pushed\n");
	}
	
	printf("Current size : %lu\n", VectorSize(myvector));
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));
	
		
	statut2 = 0;
	statut2 = VectorPushBack(myvector, (void *)20);
	
	if(statut2 == FAILED)
	{
		printf(""KRED"ERROR"KNRM" Problem with the element pushed !\n");
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" Element pushed\n");
	}
	
	printf("Current size : %lu\n", VectorSize(myvector));
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));
		
/*********************** REALLOCATE SIZE VECTOR **************************************/	
	printf(""KBLU"************** TEST REALLOCATE SIZE*********************"KNRM"\n");
	statut = VectorReserve(myvector, 30);
	
	if (statut == 1)
	{
		printf(""KRED"ERROR"KNRM" with the reallocation\n");
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" reallocation\n");
	}
	
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	
/************************** SET VALUE VECTOR ***************************************/	

	printf(""KBLU"************** TEST SET VALUE*********************"KNRM"\n");
	VectorSetElement(myvector, index10, &set);
	printf("Value %lu set to index %lu\n", set, index10);
	VectorSetElement(myvector, index15, &set2);
	printf("Value %lu set to index %lu\n", set2, index15);
	
/************************** GET VALUE VECTOR ***************************************/	

	printf(""KBLU"************** TEST GET VALUE*********************"KNRM"\n");
	printf(""KGRN"SUCCES"KNRM" The element at index : %lu is : %lu\n", index10, *(size_t *)VectorGetElement(myvector, index10));
	printf(""KGRN"SUCCES"KNRM" The element at index : %lu is : %lu\n", index15, *(size_t *)VectorGetElement(myvector, index15));
	
/*********************** TEST ADVANCED POP ***************************************/	


	printf(""KBLU"************** TEST POP******************"KNRM"\n");
	printf("Current size : %lu\n", VectorSize(myvector));
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	printf("Reserve the capacity to 8\n");
	statut = VectorReserve(myvector, 8);	
	printf(""KGRN"SUCCES"KNRM" element was poped\n");
	VectorPopBack(myvector);
	printf(""KGRN"SUCCES"KNRM" The capacity of vector was shrinked\n");
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	printf("Current size : %lu\n", VectorSize(myvector));

		
	
/*********************** SHRINK TO FIT VECTOR ***************************************/	
	printf(""KBLU"************** TEST SHRUNK*********************"KNRM"\n");
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	printf("Current size : %lu\n", VectorSize(myvector));
	
	statut3 = VectorShrinkToFit(myvector);
	
	if (statut3 == FAILED)
	{
		printf(""KRED"ERROR"KNRM" Shrunk to fit size\n");
	}
	else
	{
		printf(""KGRN"SUCCES"KNRM" Shrunk to fit size\n");
	}
	
	printf("The current capacity of the vector is : %lu\n", VectorCapacity(myvector));	
	
/************************* DESTROY VECTOR ***************************************/	
	printf(""KBLU"************** TEST DESTROY VECTOR*********************"KNRM"\n");	
	VectorDestroy(myvector);
	printf(""KGRN"SUCCES"KNRM" The vector was freed\n");

}













