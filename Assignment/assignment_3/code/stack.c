#include "stack.h"

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
