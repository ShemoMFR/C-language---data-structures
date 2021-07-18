/******************************************************************************************
*Title: Data structure
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h>
#include "bitsarr.h"

void PrintString(char *s);

int main(void)
{
	bitsarr_t arr = 0;
	char string[64];
	
	arr = BitsArrSetAll(arr);		
	BitsArrToString(arr, string);
	PrintString(string);
		
	arr = BitsArrResetAll(arr);
	BitsArrToString(arr, string);
	PrintString(string);
	
	arr = BitsArrSetOn(arr, 1);
	BitsArrToString(arr, string);
	PrintString(string);
	printf("Value of arr = %lu\n", arr);
	
	arr = BitsArrSetBit(arr, 0, 1);
	BitsArrToString(arr, string);
	PrintString(string);
	printf("Value of arr = %lu\n", arr);
		
	arr = BitsArrSetOff(arr, 50);
	
	printf("Valeur du bits position 10 : %d\n", BitsArrGetVal(arr, 10));
	
	BitsArrToString(arr, string);
	PrintString(string);	
	
	printf("Number of bits On is : %lu\n", BitsArrCountBitsOn(arr));
	printf("Number of bits Off is : %lu\n", BitsArrCountBitsOff(arr));
	
	printf("Mirror : \n");
	arr = BitsArrMirror(arr);	
	BitsArrToString(arr, string);
	PrintString(string);
	
	arr = BitsArrFlip(arr, 60);
	BitsArrToString(arr, string);
	PrintString(string);
	
	arr = BitsArrRotationLeft(arr, 1);
	BitsArrToString(arr, string);
	PrintString(string);
	
	arr = BitsArrRotationRight(arr, 1);
	BitsArrToString(arr, string);
	PrintString(string);
	
	
	
	return 0;
}

void PrintString(char *s)
{
	size_t i = 0;
	
	printf("Bits Array : ");
	
	for (; i < 64; ++i)
	{
		printf("%c", s[i]);
	}
	printf("\n");

}



