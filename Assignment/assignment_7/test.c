#include <stdio.h>

int main()
{
	char kor[500];
	for (int i = 0; i < 5; i++)
		kor[i] = 'a';
	int *count;
	int a = 3;
	count = &a;
	printf("%s (레벨 : %d)", kor, (*count));
	printf("\n");
}
