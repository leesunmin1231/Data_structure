#include <stdio.h>
#include <stdlib.h>

#define	MAX_STACK_SIZE 100
#define ARRAY_SIZE 100
#define True 1
#define False 0

typedef int Bool;
typedef struct{
	int locate[2];
	char direction;
} node;


int main()
{
	node test;
	for (int i = 0; i<2; i++)
		test.locate[i] = i+1;
	test.direction = 'r';
	printf("%c\n", test.direction);
	for (int i = 0; i<2; i++)
		printf("%d\n",test.locate[i]);
}
