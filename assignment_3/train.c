#define _CRT_SECURE_NO_WARNINGS 
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

char *print_count(int num)
{
	static char count[3];

	if (num < 10)
	{
		count[0] = '0';
		count[1] = num + '0';
	}
	else
	{
		count[0] = (num / 10) + '0';
		count[1] = (num % 10) + '0';
	}
	count[2] = '\0';
	return count;
}

void put_num(Stack *current, Stack *other, char num, int *count, int stack_num)
{
	char tmp;
	int k;
	int other_num;

	if (stack_num == 1)
		other_num = 2;
	else
		other_num = 1;

	if (isEmpty(current))
	{
		(*count)++;
		printf("%s : PUSH(%d, %c)\n",print_count(*count), stack_num, num);	
		Push(current, num);
	}
	else if (get_top(current) < num)
	{
		k = 0;
		while (get_top(current) < num && !(isEmpty(current)))
		{
			k++;
			(*count)++;
			printf("%s : POP(%d)\n",print_count(*count), stack_num);	
			tmp = Pop(current);
			(*count)++;
			printf("%s : PUSH(%d, %c)\n",print_count(*count), other_num, tmp);	
			Push(other, tmp);
		}
		(*count)++;
		printf("%s : PUSH(%d, %c)\n",print_count(*count), stack_num, num);	
		Push(current, num);
		while (k > 0)
		{
			(*count)++;
			tmp = Pop(other);
			printf("%s : POP(%d)\n",print_count(*count), other_num);	
			(*count)++;
			printf("%s : PUSH(%d, %c)\n",print_count(*count), stack_num, tmp);	
			Push(current, tmp);
			k--;
		}
	}
	else if (get_top(current) > num)
	{
		(*count)++;
		printf("%s : PUSH(%d, %c)\n",print_count(*count), stack_num, num);	
		Push(current, num);
	}
}

void three_rail(char *train_num)
{
	char out[ARRAY_SIZE];
	int stack_count = 3;
	Stack **rail = (Stack **)malloc(sizeof(Stack *) * stack_count);
	if (rail == 0)
		return ;
	int i = 0;
	int j = 0;
	char tmp;
	int count = 0;
	char recent_out = '0';
	while (j < stack_count)
	{
		rail[j] = (Stack *)malloc(sizeof(Stack));
		if (rail[j] == 0)
			return ;
		rail[j] = Create();
		j++;
	}
	j = 0;
	while (train_num[i])
	{
		count++;
		printf("%s : ",print_count(count));
		printf("IN(%c)\n",train_num[i]);
		if (train_num[i] == (recent_out + 1))
		{
			count++;
			printf("%s : ",print_count(count));
			printf("OUT(%c)\n",train_num[i]);
			out[j++] = train_num[i];
			recent_out++;
			i++;
			if (!isEmpty(rail[0]) && (recent_out + 1) == get_top(rail[0]))
			{
				count++;
				printf("%s : POP(%d)\n",print_count(count), 1);
				count++;
				tmp = Pop(rail[0]);
				printf("%s : OUT(%c)\n",print_count(count), tmp);
				out[j++] = tmp;
				recent_out++;
			}
			else if (!isEmpty(rail[1]) && (recent_out + 1) == get_top(rail[1]))
			{
				count++;
				printf("%s : POP(%d)\n",print_count(count), 2);
				count++;
				tmp = Pop(rail[1]);
				printf("%s : OUT(%c)\n",print_count(count), tmp);
				out[j++] = tmp;
				recent_out++;
			}
			else if (!isEmpty(rail[2]) && (recent_out + 1) == get_top(rail[2]))
			{
				count++;
				printf("%s : POP(%d)\n",print_count(count), 3);
				count++;
				tmp = Pop(rail[2]);
				printf("%s : OUT(%c)\n",print_count(count), tmp);
				out[j++] = tmp;
				recent_out++;
			}
			continue;
		}
		if (train_num[i] <= '4' && train_num[i] > '1')
			put_num(rail[0], rail[1], train_num[i], &count, 1);
		else if (train_num[i] <= '7' && train_num[i] > '4')
			put_num(rail[1], rail[0], train_num[i], &count, 2);
		else
			put_num(rail[2], rail[0], train_num[i], &count, 3);
		i++;
	}
	while (!isEmpty(rail[0]))
	{
		count++;
		printf("%s : POP(%d)\n",print_count(count), 1);
		count++;
		tmp = Pop(rail[0]);
		printf("%s : OUT(%c)\n",print_count(count), tmp);
		out[j++] = tmp;
		recent_out++;
	}
	while (!isEmpty(rail[1]))
	{
		count++;
		printf("%s : POP(%d)\n",print_count(count), 2);
		count++;
		tmp = Pop(rail[1]);
		printf("%s : OUT(%c)\n",print_count(count), tmp);
		out[j++] = tmp;
		recent_out++;
	}
	while (!isEmpty(rail[2]))
	{
		count++;
		printf("%s : POP(%d)\n",print_count(count), 2);
		count++;
		tmp = Pop(rail[2]);
		printf("%s : OUT(%c)\n",print_count(count), tmp);
		out[j++] = tmp;
		recent_out++;
	}
	out[j] = '\0';
	for (i = 0; i < stack_count; i++)
		free(rail[i]);
	free(rail);
	printf("종료(총 %d회)\n",count);
}

void two_rail(char *train_num)
{
	char out[ARRAY_SIZE];
	int stack_count = 2;
	Stack **rail = (Stack **)malloc(sizeof(Stack *) * stack_count);
	if (rail == 0)
		return ;
	int i = 0;
	int j = 0;
	char tmp;
	int count = 0;
	char recent_out = '0';
	while (j < stack_count)
	{
		rail[j] = (Stack *)malloc(sizeof(Stack));
		if (rail[j] == 0)
			return ;
		rail[j] = Create();
		j++;
	}
	j = 0;
	while (train_num[i])
	{
		count++;
		printf("%s : ", print_count(count));
		printf("IN(%c)\n",train_num[i]);
		if (train_num[i] == (recent_out + 1))
		{
			count++;
			printf("%s : ",print_count(count));
			printf("OUT(%c)\n",train_num[i]);
			out[j++] = train_num[i];
			recent_out++;
			i++;
			if (!isEmpty(rail[0]) && (recent_out + 1) == get_top(rail[0]))
			{
				count++;
				printf("%s : POP(%d)\n",print_count(count), 1);
				count++;
				tmp = Pop(rail[0]);
				printf("%s : OUT(%c)\n",print_count(count), tmp);
				out[j++] = tmp;
				recent_out++;
			}
			else if (!isEmpty(rail[1]) && (recent_out + 1) == get_top(rail[1]))
			{
				count++;
				printf("%s : POP(%d)\n",print_count(count), 2);
				count++;
				tmp = Pop(rail[1]);
				printf("%s : OUT(%c)\n",print_count(count), tmp);
				out[j++] = tmp;
				recent_out++;
			}
			continue;
		}
		if (train_num[i] <= '5' && train_num[i] > '1')
			put_num(rail[0], rail[1], train_num[i], &count, 1);
		else
			put_num(rail[1], rail[0], train_num[i], &count, 2);
		i++;
	}
	while (!isEmpty(rail[0]))
	{
		count++;
		printf("%s : POP(%d)\n",print_count(count), 1);
		count++;
		tmp = Pop(rail[0]);
		printf("%s : OUT(%c)\n",print_count(count), tmp);
		out[j++] = tmp;
		recent_out++;
	}
	while (!isEmpty(rail[1]))
	{	
		count++;
		printf("%s : POP(%d)\n",print_count(count), 2);
		count++;
		tmp = Pop(rail[1]);
		printf("%s : OUT(%c)\n",print_count(count), tmp);
		out[j++] = tmp;
		recent_out++;
	}
	out[j] = '\0';

	for (i = 0; i < stack_count; i++)
		free(rail[i]);
	free(rail);
	printf("종료(총 %d회)\n",count);
}

int main()
{
	int stack_count;
	char train_num[ARRAY_SIZE];
	printf("스택의 개수: ");
	scanf("%d",&stack_count);
	printf("열차 번호 입력: ");
	scanf("%s",train_num);
	if (stack_count == 2)
		two_rail(train_num);
	else if (stack_count == 3)
		three_rail(train_num);	
	else
	{
		printf("스택의 개수는 2개에서 3개 입니다.\n");
		return (1);
	}

}

