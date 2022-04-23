#include <stdio.h>

#define swap(x,y,t) ( (t) = (y), (y) = (x), (x) = (t))

void bubble_sort(int arr[], int size)
{
	int i, j, tmp;

	for (i = size - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1], tmp);
		}
	}
}

int main()
{
	int arr[6] = {5,3,9,1,2,7};
	bubble_sort(arr, 6);
	for (int i = 0; i < 6; i++)
		printf("%d ",arr[i]);
}
