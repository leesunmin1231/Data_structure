#ifndef STACK_H
# define STACK_H
# include <stdio.h>
# include <stdlib.h>

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

Stack *Create(void);
Bool isEmpty(Stack *pstack);
Bool isFull(Stack *pstack);
void Push(Stack *pstack, Element Data);
Element Pop(Stack *pstack);
Element get_top(Stack *pstack);

# endif
