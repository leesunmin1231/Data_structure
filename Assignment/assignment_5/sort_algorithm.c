#define _CRT_SECURE_NO_WARNINGS 
#include <time.h>
#include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define ARR_SIZE 20000
void quicksort(char arr[ARR_SIZE][12], int size);
void selection_sort(char arr[ARR_SIZE][12], int size);
void heap_sort(char arr[ARR_SIZE][12], int size);

void init_array(char arr[ARR_SIZE][12], char origin[ARR_SIZE][12], int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
		strcpy(arr[i], origin[i]);
}

void print_array(char name[ARR_SIZE][12])
{
	for (int i = 0; i < ARR_SIZE; i++)
		printf("%s ", name[i]);
	printf("\n");
}

void random_id(char id[ARR_SIZE][12], int size)
{
	int i,j,tmp;
	int count[4] = {0,0,0,0};
	int arr[ARR_SIZE];
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		tmp = rand()%4;
		if (count[tmp] < ARR_SIZE/4)
		{
			arr[i] = rand()% 10000 + (tmp + 1)*10000 + 20180000;
			count[tmp]++;
		}
		else if (i == size)
			break;
		else
		{
			i--;
			continue;
		}
		for (j = 0; j < i; j++)
			if (arr[i] == arr[j])
			{
				count[tmp]--;
				i--;
			}
	}
	for (i = 0; i < size; i++)
	{
		sprintf(id[i], "%d", arr[i]);
	}

}

void random_name(char arr[ARR_SIZE][12], int size)
{
	int i,j,index;
	char alpha[30] = "abcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 10; j++)
		{
			index = rand()%26;
			arr[i][j] = alpha[index];
		}
		arr[i][j] = '\0';
	}
}

void random_number(char arr[ARR_SIZE][12] , int size)
{
	int i,j;
	char num[11] = "0123456789";
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		arr[i][0] = '0';
		arr[i][1] = '1';
		arr[i][2] = '0';
		for (j = 3; j < 11; j++)
			arr[i][j] = num[rand()%10];
		arr[i][j] = '\0';
	}
}

double check_qsort_time(char arr[ARR_SIZE][12], char origin[ARR_SIZE][12], void fp (void *, unsigned long, unsigned long, int (*)(const void *, const void *)))
{
	clock_t start, end;
	start = clock();
	fp(arr, ARR_SIZE, sizeof(char[12]), (void *)strcmp);
	end = clock();
	double runtime = (double)(end - start);
	print_array(arr);
	printf("Execution time : %.0lf ms \n", runtime);
	init_array(arr, origin, ARR_SIZE);
	return runtime;
}

double check_time(char arr[ARR_SIZE][12], char origin[ARR_SIZE][12], void fp (char arr[ARR_SIZE][12], int))
{
	clock_t start, end;
	start = clock();
	fp(arr, ARR_SIZE);
	end = clock();
	double runtime = (double)(end - start);
	print_array(arr);
	printf("Execution time : %.0lf ms \n", runtime);
	init_array(arr, origin, ARR_SIZE);
	return runtime;
}

int main()
{
	char id[ARR_SIZE][12];
	char name[ARR_SIZE][12];
	char number[ARR_SIZE][12]; 
	char id_origin[ARR_SIZE][12];
	char name_origin[ARR_SIZE][12];
	char number_origin[ARR_SIZE][12];
	double runtime_arr[50];
	int count = 0;

	random_id(id, ARR_SIZE);
	random_name(name, ARR_SIZE);
	random_number(number, ARR_SIZE);
	print_array(id);
	print_array(name);
	print_array(number);
	init_array(id_origin, id, ARR_SIZE);
	init_array(name_origin, name, ARR_SIZE);
	init_array(number_origin, number, ARR_SIZE);

	printf("Use qsort to id array\n");
	runtime_arr[count++] = check_qsort_time(id, id_origin, qsort);

	printf("Use qsort to name array\n");
	runtime_arr[count++] = check_qsort_time(name, name_origin, qsort);
	
	printf("Use qsort to number array\n");
	runtime_arr[count++] = check_qsort_time(number, number_origin, qsort);
	
	printf("Use my quicksort code to id array\n");
	runtime_arr[count++] = check_time(id, id_origin, quicksort);

	printf("Use my quicksort code to name array\n");
	runtime_arr[count++] = check_time(name, name_origin, quicksort);

	printf("Use my quicksort code to number array\n");
	runtime_arr[count++] = check_time(number, number_origin, quicksort);

	printf("Use my selection sort code to id array\n");
	runtime_arr[count++] = check_time(id, id_origin, selection_sort);

	printf("Use my selection sort code to name array\n");
	runtime_arr[count++] = check_time(name, name_origin, selection_sort);

	printf("Use my selection sort code to number array\n");
	runtime_arr[count++] = check_time(number, number_origin, selection_sort);

	printf("Use my heap sort code to id array\n");
	runtime_arr[count++] = check_time(id, id_origin, heap_sort);

	printf("Use my heap sort code to name array\n");
	runtime_arr[count++] = check_time(name, name_origin, heap_sort);

	printf("Use my heap sort code to number array\n");
	runtime_arr[count++] = check_time(number, number_origin, heap_sort);

	printf("qsort, id array :     %.0lf, quicksort id array:     %.0lf\n", runtime_arr[0], runtime_arr[3]);
	printf("qsort, name array :   %.0lf, quicksort name array:   %.0lf\n", runtime_arr[1], runtime_arr[4]);
	printf("qsort, number array : %.0lf, quicksort number array: %.0lf\n", runtime_arr[2], runtime_arr[5]);
	printf("quicksort id array:     %.0lf, selection sort id array:     %.0lf, heap sort id array:     %.0lf\n", runtime_arr[3], runtime_arr[6], runtime_arr[9]);
	printf("quicksort name array:   %.0lf, selection sort name array:   %.0lf, heap sort name array:   %.0lf\n", runtime_arr[4], runtime_arr[7], runtime_arr[10]);
	printf("quicksort number array: %.0lf, selection sort number array: %.0lf, heap sort number array: %.0lf\n", runtime_arr[5], runtime_arr[8], runtime_arr[11]);

	return (0);
}
