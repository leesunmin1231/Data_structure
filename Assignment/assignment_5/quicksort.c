int get_pivot(int *arr, int start, int end)
{
	int pivot = arr[end];
	int tmp;
	int i = start - 1;
	int j = start;
	while (j < end)
	{
		if (arr[j] < pivot){
			tmp = arr[++i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		j++;
	}
	tmp = arr[i+1];
	arr[i + 1] = arr[end];
	arr[end] = tmp;
	return (i + 1);
}

void quick_recur(int *arr, int start, int end)
{
	if (start >= end)
		return ;
	int pivot_idx;

	pivot_idx = get_pivot(arr, start, end);
	quick_recur(arr, start, pivot_idx - 1);
	quick_recur(arr, pivot_idx + 1, end);
}

void quicksort_num(int *arr, int size, )
{
	quick_recur(arr, 0, size-1);
}

void quicksort_
