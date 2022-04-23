#include <stdio.h>

#define swap(x,y,t) ( (t) = (y), (y) = (x), (x) = (t))

void selection_sort(int arr[], int size)
{
	int i, j, min, tmp;
	for (i = 0; i < size; i++)
	{
		min = arr[i];
		tmp = i;
		for (j = i; j < size; j++)
		{
			if (min > arr[j])
			{
				tmp = j;
				min = arr[j];
			}
		}
		swap(arr[i], arr[tmp], min);
	}
}

int main()
{
	int arr[6] = {5,3,9,1,2,7};

	selection_sort(arr, 6);
	for (int i = 0; i < 6; i++)
		printf("%d\n", arr[i]);
}
