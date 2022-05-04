#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define ARR_SIZE 20000

void selection_sort(char arr[ARR_SIZE][12], int size)
{
	int i, j, tmp;
	char min[12];
	for (i = 0; i < size; i++)
	{
		strcpy(min,arr[i]);
		tmp = i;
		for (j = i; j < size; j++)
		{
			if (strcmp(min, arr[j]) > 0)
			{
				tmp = j;
				strcpy(min, arr[j]);
			}
		}
		if (i != tmp)
		{
			strcpy(min,arr[i]);
			strcpy(arr[i], arr[tmp]);
			strcpy(arr[tmp],min);
		}
	}
}
