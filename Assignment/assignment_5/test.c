#include <stdio.h>
#define ARR_SIZE 10
void quicksort(char arr[ARR_SIZE][12], int size);

int main()
{
	char arr[10][12] = {"z", "c", "a", "b", "d", "g","a", "f", "c", "a"};
	int i;
	for (i = 0; i < 10; i++)
		printf("%s ",arr[i]);
	printf("\n");
	quicksort(arr, 10);
	for (i = 0; i < 10; i++)
		printf("%s ",arr[i]);
}
