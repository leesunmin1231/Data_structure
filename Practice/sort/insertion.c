#include <stdio.h>

#define swap(x, y, t) (t) = (y), (y) = (x), (x) = (t)

void insertion_sort(int list[], int n)
{
	int i,j,key;
	for (i = 0; i < n; i++)
	{
		tmp = list[i];
		for (j = i-1; j >= 0 && list[j] > key; j--)
		{
			list[j + 1] = list[j];
		}
		list[j+1] = key;
	}
}



