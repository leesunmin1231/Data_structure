#define _CRT_SECURE_NO_WARNINGS 
#include <string.h>

#define ARR_SIZE 20000

void heapify(char arr[ARR_SIZE][12], int here, int size) {
	int left = here * 2 + 1;
    	int right = here * 2 + 2;
    	char temp[12];
    	int max=here;
    	if (left < size && strcmp(arr[left],arr[max]) > 0)
        	max = left;
    	if (right < size && strcmp(arr[right],arr[max]) > 0)
        	max = right;

    	if (max != here) {
		strcpy(temp, arr[here]);
		strcpy(arr[here], arr[max]);
		strcpy(arr[max], temp);
        	heapify(arr, max, size);
    	}
}

void buildHeap(char arr[ARR_SIZE][12], int size) {
    	int i,j;
    	for (i = size / 2 - 1; i >= 0; i--) {
        	heapify(arr, i, size);
    	}
}

void heap_sort(char arr[ARR_SIZE][12],int size) {
    	int treeSize;
    	char temp[12];
    	buildHeap(arr, size);
    	for (treeSize = size - 1; treeSize >= 0; treeSize--)
	{
		if (treeSize != 0)
	    	{
		    	strcpy(temp, arr[0]);
		    	strcpy(arr[0], arr[treeSize]);
		    	strcpy(arr[treeSize], temp);
	    	}
	    	heapify(arr, 0,treeSize);
    	}
}
