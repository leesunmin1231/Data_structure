#include <time.h>
#include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define ARR_SIZE 5000


void init_array(void *arr, void *origin, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
		((unsigned int *)arr)[i] = ((unsigned int *)origin)[i];
}

void print_number(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void print_str(char name[ARR_SIZE][12])
{
	for (int i = 0; i < ARR_SIZE; i++)
		printf("%s ", name[i]);
	printf("\n");
}

void random_id(int *arr, int size)
{
	int i,j;
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		arr[i] = rand()% 40000 + 20190000;
		for (j = 0; j < i; j++)
			if (arr[i] == arr[j])
				i--;
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


int numcmp_ascend(const void *a, const void *b)
{
	int num1 = *(int *)a;
	int num2 = *(int *)b;
	
	if (num1 < num2)
        	return -1;
    
    	if (num1 > num2)
        	return 1;
    	return 0;
}

int str_descend(const void* a, const void* b) {
    return strcmp(*(char**)b,*(char**)a);
}

int main(int argc, char **argv)
{
	int id[ARR_SIZE];
	char name[ARR_SIZE][12];
	char number[ARR_SIZE][12]; 
	int id_origin[ARR_SIZE];
	char name_origin[ARR_SIZE][12];
	char number_origin[ARR_SIZE][12];
	clock_t start, end;
	double runtime;

	random_id(id, ARR_SIZE);
	random_name(name, ARR_SIZE);
	random_number(number, ARR_SIZE);
	// print_number(id, ARR_SIZE);
	// print_str(name);
	// print_str(number);
	init_array(id_origin, id, ARR_SIZE);
	init_array(name_origin, name, ARR_SIZE);
	init_array(number_origin, number, ARR_SIZE);

	printf("use qsort to id array\n");
	start = clock();
	qsort(id, ARR_SIZE, sizeof(int), numcmp_ascend);
	end = clock();
	runtime = (double)(end - start);
	print_number(id, ARR_SIZE);
	printf("Execution time : %.0lf ms \n", runtime);
	init_array(id, id_origin, ARR_SIZE);

	printf("use qsort to name array\n");
	start = clock();
	qsort(name, ARR_SIZE, sizeof(char[12]), (void *)strcmp);
	end = clock();
	runtime = (double)(end - start);
	print_str(name);
	printf("Execution time : %.0lf ms \n", runtime);
	init_array(name, name_origin, ARR_SIZE);

	printf("use qsort to number array\n");
	start = clock();
	qsort(number, ARR_SIZE, sizeof(char[12]), (void *)strcmp);
	end = clock();
	runtime = (double)(end - start);
	print_str(number);
	printf("Execution time : %.0lf ms \n", runtime);
	init_array(number, number_origin, ARR_SIZE);
}
