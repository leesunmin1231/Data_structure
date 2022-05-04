#define _CRT_SECURE_NO_WARNINGS 
#include <string.h>

#define ARR_SIZE 20000

void adjust(char arr[ARR_SIZE][12], int root, int n)
{
	int child;
	char tmp[20];
	char rootkey[20];
       	strcpy(tmp, arr[root]);
	strcpy(rootkey, arr[root]);
	child = 2*root;
	while (child <= n)
	{
		if ((child < n) && (strcmp(arr[child], arr[child + 1]) < 0))
			child++;
		if(strcmp(rootkey, arr[child]) > 0)
			break;
		else
		{
			if (child/2 != child)
				strcpy(arr[child/2], arr[child]);
			child *= 2;
		}
	}
	strcpy(arr[child/2], tmp);
}

void heap_sort(char arr[ARR_SIZE][12], int size)
{
	int i;
	char temp[20];
	for (i = size/2; i > 0; i--)
		adjust(arr, i, size);
	for (i = size - 1; i > 0; i--)
	{
		if (i+1 != 1)
		{
			strcpy(temp, arr[1]);
			strcpy(arr[1], arr[i+1]);
			strcpy(arr[i+1], temp);
		}
		adjust(arr, 1, i);
	}
}
