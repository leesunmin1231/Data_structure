#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ARR_SIZE 5000

int get_pivot(char arr[ARR_SIZE][12], int start, int end)
{
	char pivot[12];
	char tmp[12];
	int i = start - 1;
	int j = start;
	strcpy(pivot, arr[end]);
	while (j < end)
	{
		if (strcmp(arr[j],pivot) < 0){
			i++;
			if (i != j)
			{
				strcpy(tmp, arr[i]);
				strcpy(arr[i], arr[j]);
				strcpy(arr[j], tmp);
			}
		}
		j++;
	}
	if (i+1 != end)
	{
		strcpy(tmp,arr[i+1]);
		strcpy(arr[i + 1], arr[end]);
		strcpy(arr[end],tmp);
	}
	return (i + 1);
}

void quick_recur(char arr[ARR_SIZE][12], int start, int end)
{
	if (start >= end)
		return ;
	int pivot_idx;

	pivot_idx = get_pivot(arr, start, end);
	quick_recur(arr, start, pivot_idx - 1);
	quick_recur(arr, pivot_idx + 1, end);
}

void quicksort(char arr[ARR_SIZE][12], int size)
{
	quick_recur(arr, 0, size-1);
}
