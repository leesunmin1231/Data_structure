#include <stdio.h>
#include <stdlib.h>

#define	MAX_STACK_SIZE 100
#define ARRAY_SIZE 100
#define True 1
#define False 0

typedef int Bool;
typedef char Element;
typedef struct{
	Element stackArr[MAX_STACK_SIZE];
	int top;
} Stack;

Stack *Create(void) {
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));
	if (new_stack == 0)
		return 0;
	new_stack -> top = -1;
	return new_stack;
}

Bool isEmpty(Stack *pstack)
{
	if (pstack -> top == -1)
		return True;
	return False;
}

Bool isFull(Stack *pstack)
{
	if (pstack -> top == MAX_STACK_SIZE - 1)
		return True;
	return False;
}

void Push(Stack *pstack, Element Data)
{
	pstack->stackArr[++pstack->top] = Data;
}

Element Pop(Stack *pstack)
{
	return pstack->stackArr[pstack->top--];
}

Element get_top(Stack *pstack)
{
	return pstack -> stackArr[pstack->top];
}

void find_road(char **maze, int row, int col)
{
	// index 짝수 : 벽, 홀수 : 길
		

int main()
{
	char buffer[ARRAY_SIZE];
	FILE *fp = fopen("maze1.txt", "r");
	fgets(buffer, sizeof(buffer), fp);
	int col = atoi(buffer);
	int i = 0;
       	while (buffer[i] != ' ')
		i++;
	int row = atoi(&buffer[i]);
	printf("row : %d, col: %d\n",row, col);
	char **maze = (char **)malloc(sizeof(char *) * (row * 2 + 1));
	for (i = 0; i < (row * 2 + 1); i++)
	{
		fgets(buffer,sizeof(buffer),fp);
		maze[i] = buffer;
		printf("%s", buffer);
	}
	find_road(maze, row, col);
	free(maze);
	fclose(fp);
	return (0);
}
