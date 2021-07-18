/******************************************************************************************
*Title: tree
*Author : 
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h> /* printf */
#include "tree.h" 

void TestTree();
void IntCompare(int input, int output, char *string);

enum end_prog
{
	SUCCESS = 0, FAILED = 1
};

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"

int main(void)
{
	TestTree();
	
	return SUCCESS;
}

void TestTree()
{
	node_t *root = NULL; 
	root = BstInsert(root, 50); 
	
	printf(""KBLU"--------- TEST IS EMPTY --------\n"KNRM"");
	IntCompare(IsEmpty(root), 1, "Empty");
	
    BstInsert(root, 30); 
    BstInsert(root, 20); 
    BstInsert(root, 40); 
    BstInsert(root, 70); 
    BstInsert(root, 60); 
    BstInsert(root, 80); 
    BstInsert(root, 90);
    
    printf(""KBLU"--------- TEST DISPLAY TREE --------\n"KNRM"");
  
  	printf(""KGRN"------ TREE -------"KNRM"\n");
    BstPrintInOrder(root, 3); 
  	IntCompare(BstSearchNumber(root, 80), 1, "Research");
  	
  	BstDelete(root);
}

void IntCompare(int input, int output, char *string)
{
	if (input == output)
	{
		printf(""KGRN"SUCCESS"KNRM" %s in the tree\n", string);
	}
	else
	{
		printf(""KRED"ERROR"KNRM" %s in the tree\n", string);
	}
}

