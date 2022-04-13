#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_STACK_SIZE 100
#define ARRAY_SIZE 100
#define True 1
#define False 0

typedef int Bool;
typedef struct{
	int locate[2];
	char direction;
} node;

typedef struct{
	node stackArr[MAX_STACK_SIZE];
	int top;
} Stack;

node create_node(int i, int j, char dir)
{
	node new_node;
	new_node.locate[0] = i / 2;
	new_node.locate[1] = j / 2;
	new_node.direction = dir;
	return new_node;
}

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

void Push(Stack *pstack, node Data)
{
	pstack->stackArr[++pstack->top] = Data;
}

node Pop(Stack *pstack)
{
	return pstack->stackArr[pstack->top--];
}

node get_top(Stack *pstack)
{
	return pstack -> stackArr[pstack->top];
}

Bool check_go(char **maze, int i, int j, char dir)
{
	switch (dir){
	case 'r':
		if (maze[i][j+1] == ' ')
			return (True);
		break;
	case 'l':
		if (maze[i][j-1] == ' ')
			return (True);
		break;
	case 'd':
		if (maze[i+1][j] == ' ')
			return (True);
		break;
	case 'u':
		if (maze[i-1][j] == ' ')
			return (True);
		break;
	}
	return (False);
}



void find_road(char **maze, int row, int col)
{
	// index 짝수 : 벽, 홀수 : 길
	char road_dir[4];
	char prev_dir = 'r'; 
	Stack *pstack = Create();
	int count;
	int road_count = 0;
	int i = 1;
	int j = 1;
	while (True)
	{
		count = 0;
		switch (prev_dir){
		case 'r':
			if (check_go(maze, i, j,'r'))
				road_dir[count++] = 'r';
			if (check_go(maze, i, j,'u'))
				road_dir[count++] = 'u';
			if (check_go(maze, i, j,'d'))
				road_dir[count++] = 'd';
			break;
		case 'l':
			if (check_go(maze, i, j,'l'))
				road_dir[count++] = 'l';
			if (check_go(maze, i, j,'u'))
				road_dir[count++] = 'u';
			if (check_go(maze, i, j,'d'))
				road_dir[count++] = 'd';
			break;
		case 'u':
			if (check_go(maze, i, j,'r'))
				road_dir[count++] = 'r';
			if (check_go(maze, i, j,'l'))
				road_dir[count++] = 'l';
			if (check_go(maze, i, j,'u'))
				road_dir[count++] = 'u';
			break;
		case 'd':
			if (check_go(maze, i, j,'r'))
				road_dir[count++] = 'r';
			if (check_go(maze, i, j,'l'))
				road_dir[count++] = 'l';
			if (check_go(maze, i, j,'d'))
				road_dir[count++] = 'd';
			break;
		}
		if (count == 0) // 길이 없을 때
		{
			if (isEmpty(pstack))
				break;
			node cross = Pop(pstack);
			printf("POP(%d,%d,%c)\n",cross.locate[0],cross.locate[1],cross.direction);
			switch (cross.direction){
			case 'r':
				i = cross.locate[0] * 2 + 1;
				j = cross.locate[1] * 2 + 3;
				break;
			case 'l':
				i = cross.locate[0] * 2 + 1;
				j = cross.locate[1] * 2 - 1;
				break;
			case 'u':
				i = cross.locate[0] * 2 - 1;
				j = cross.locate[1] * 2 + 1;
				break;
			case 'd':
				i = cross.locate[0] * 2 + 3;
				j = cross.locate[1] * 2 + 1;
				break;
			}
			prev_dir = cross.direction;
			continue;
		}
		else if (count > 1)
		{
			for (int k = 1; k < count; k++)
			{
				node new_cross = create_node(i,j,road_dir[k]);
				Push(pstack, new_cross);
				printf("PUSH(%d,%d,%c)\n",i/2,j/2,road_dir[k]);
			}
		}
		if (i == (row * 2 - 1) && j == (col * 2 - 1))
		{
			road_count++;
			if (isEmpty(pstack))
				break;
			else
			{
				node cross = Pop(pstack);
				printf("POP(%d,%d,%c)\n",cross.locate[0],cross.locate[1],cross.direction);
				switch (cross.direction){
				case 'r':
					i = cross.locate[0] * 2 + 1;
					j = cross.locate[1] * 2 + 3;
					break;
				case 'l':
					i = cross.locate[0] * 2 + 1;
					j = cross.locate[1] * 2 - 1;
					break;
				case 'u':
					i = cross.locate[0] * 2 - 1;
					j = cross.locate[1] * 2 + 1;
					break;
				case 'd':
					i = cross.locate[0] * 2 + 3;
					j = cross.locate[1] * 2 + 1;
					break;
				}
				prev_dir = cross.direction;
				continue;
			}
		}	
		prev_dir = road_dir[0];
		switch (prev_dir){
		case 'r':
			j += 2;
			break;
		case 'l':
			j -= 2;
			break;
		case 'u':
			i -= 2;
			break;
		case 'd':
			i += 2;
			break;
		}
	}
	printf("모두 %d개의 길을 찾았습니다.\n", road_count);
	free(pstack);		
}
int main()
{
	char buffer[ARRAY_SIZE];
	FILE *fp = fopen("maze3.txt", "r");
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
		maze[i] = (char *)malloc(col * 2 + 2);
		strcpy(maze[i],buffer);
		printf("%s", maze[i]);
	}
	find_road(maze, row, col);
	for (i = 0; i < (row * 2 + 1); i++)
		free(maze[i]);
	free(maze);
	fclose(fp);
	return (0);
}
