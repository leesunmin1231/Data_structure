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

Bool compare_op(Stack *pstack, char op)
{
	char current = pstack->stackArr[pstack->top];

	if (current == '*' || current == '/')
		return True;
	else if (current == '+' || current == '-')
	{
		if (op == '+' || op == '-' || op == '(')
			return True;
		else
			return False;
	}
	else
		return False;
}

Bool is_operator(char c)
{
	char op[10] = {'+','-','*','/','(',')'};
	int i = 0;
	while (op[i])
	{
		if (op[i] == c)
			return True;
		i++;
	}
	return False;
}

Bool is_number(char c)
{
	if (c >= '0' && c <= '9')
		return True;
	else
		return False;
}

void get_result(Stack *calstack, char *num1, char *num2, char op)
{
	int num1_len = 0;
	int num2_len = 0;
	int result_len = 0;
	int zero_count = 0;
	int dot_flag = 0;
	int i;
	float result;
	char n1[ARRAY_SIZE];
	char n2[ARRAY_SIZE];
	while (num1[num1_len])
		num1_len++;
	while (num2[num2_len])
		num2_len++;
	for (i = 0; i < num1_len; i++)
		n1[i] = num1[num1_len - i - 1];
	n1[i] = '\0';
	for (i = 0; i < num2_len; i++)
		n2[i] = num2[num2_len - i - 1];
	n2[i] = '\0';
	switch (op){
	case '*':
		result = atof(n1) * atof(n2);
		break;
	case '+':
		result = atof(n1) + atof(n2);
		break;
	case '-':
		result = atof(n1) - atof(n2);
		break;
	case '/':
		result = atof(n1) / atof(n2);
		break;
	default:
		return;
	}
	sprintf(n1, "%f", result);
	Push(calstack, ' ');
	while (n1[result_len])
	{
		if (n1[result_len] == '.')
			dot_flag = 1;
		if (dot_flag == 1 && n1[result_len] == '0')
			zero_count++;
		if (dot_flag == 1 && n1[result_len] != '0')
			zero_count = 0;
		Push(calstack, n1[result_len++]);
		if (zero_count >= 3)
		{
			while (zero_count > 0)
			{
				Pop(calstack);
				zero_count--;
			}
			break;
		}
	}
	if (get_top(calstack) == '.')
		Pop(calstack);
	Push(calstack, ' ');
}

void to_postfix(char *formula, char *postfix)
{
	char tmp;
	Stack *opstack = Create();
	int i,j;

	i = 0;
	j = -1;
	while (formula[i])
	{
		if (formula[i] == ' ')
		{
			i++;
			continue;
		}
		else if (is_operator(formula[i])){
			if (formula[i] != '(' && formula[i] != ')')
				postfix[++j] = ' ';
			if (isEmpty(opstack))
				Push(opstack, formula[i]);
			else{
				if (formula[i] == ')')
				{
					tmp = ')';
					while (tmp != '(')
					{
						tmp = Pop(opstack);
						if (tmp != '(')
							postfix[++j] = tmp;
					}
				}
				else if (formula[i] == '(')
					Push(opstack, formula[i]);
				else if (compare_op(opstack, formula[i]))
				{
					postfix[++j] = Pop(opstack);
					Push(opstack, formula[i]);
				}
				else
					Push(opstack, formula[i]);
			}
		}
		else
			postfix[++j] = formula[i];
		i++;
	}
	while (!isEmpty(opstack))
	{
		postfix[++j] = Pop(opstack);
	}
	postfix[++j] = '\0';
	free (opstack);
}

void	calculate(char *formula)
{
	char postfix[ARRAY_SIZE];
	char tmp;
	char num1_arr[ARRAY_SIZE];
	char num2_arr[ARRAY_SIZE];
	char result[ARRAY_SIZE];
	Stack *calstack = Create();
	int i = 0;
	int j = 0;

	to_postfix(formula, postfix);
	while (postfix[i])
	{
		if (is_number(postfix[i]) || postfix[i] == '.' || postfix[i] == ' ')
			Push(calstack, postfix[i]);
		else if (is_operator(postfix[i]))
		{
			j = 0;
			tmp = postfix[i];
			while (get_top(calstack) == ' ')
				Pop(calstack);
			while (tmp != ' ' && !(isEmpty(calstack)))
			{
				tmp = Pop(calstack);
				num2_arr[j++] = tmp;
			}
			num2_arr[j] = '\0';
			j = 0;
			tmp = postfix[i];
			while (get_top(calstack) == ' ')
				Pop(calstack);
			while (tmp != ' ' && !(isEmpty(calstack)))
			{
				tmp = Pop(calstack);
				num1_arr[j++] = tmp;
			}
			num1_arr[j] = '\0';
			get_result(calstack, num1_arr, num2_arr, postfix[i]);
		}
		i++;
	}
	i = 0;
	while (!isEmpty(calstack))
	{
		if (get_top(calstack) == ' ')
			Pop(calstack);
		else
			result[i++] = Pop(calstack);
	}
	printf("= ");
	while (i >= 0)
		printf("%c",result[--i]);
	printf("\n");
	free (calstack);	
}

int	check_formula(char *formula)
{
	int i = 0;
	int flag = 0;
	if (!(is_number(formula[i]) || formula[i] == '('))
		return 0;
	if (formula[i++] == '(')
		flag = 1;
	while (formula[i])
	{
		if (is_operator(formula[i-1]) && is_operator(formula[i]))
		{
			if (formula[i] != '(' && formula[i-1] != ')')
				return i;
		}
		if (formula[i] == '.')
		{
			if (is_operator(formula[i-1]))
				return i;
		}
		if (formula[i - 1] == '.')
			if (is_operator(formula[i]) || formula[i] == '.')
				return i;
		if (formula[i] == '(')
			flag = 1;
		else if (formula[i] == ')' && flag == 1)
			flag = 0;
		else if (formula[i] == ')' && flag == 0)
			return i;
		i++;
	}
	if ((is_operator(formula[--i]) && formula[i] != ')') || flag == 1)
		return i;
	return -1;
}

int main()
{
	char formula[ARRAY_SIZE];
	scanf("%s",formula);
	int index = check_formula(formula);
	int i;
	if (index != -1)
	{
		for (i = 0; i < index; i++)
			printf(" ");
		while (formula[i] && is_number(formula[i]))
		{
			printf(" ");
			i++;
		}
		printf("^ 이 위치에 오류가 있습니다.\n");
		return 1;
	}
	calculate(formula);
}
