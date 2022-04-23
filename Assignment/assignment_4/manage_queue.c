#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define	MAX_QUEUE_SIZE 21
#define ARRAY_SIZE 100
#define True 1
#define False 0

typedef int Bool;

typedef struct{
	char queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
} QueueType;

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}

QueueType *create(void)
{
	QueueType *new_queue = (QueueType *)malloc(sizeof(QueueType));
	new_queue->front = 0;
	new_queue->rear = 0;
	return new_queue;
}

void enqueue(QueueType *q, char item)
{
	if (is_full(q))
	{
		printf("(SYSTEM) ADDQUEUE() FAIL. QueueFull\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
	printf("(SYSTEM) ADDQUEUE(%c) F=%d R=%d\n",item, q->front, q->rear);
}

char dequeue(QueueType *q)
{
	if (is_empty(q))
	{
		printf("DELETEQUEUE() FAIL. QueueEmpty\n");
		return 0;
	}
	q -> front = (q->front+1) % MAX_QUEUE_SIZE;
	printf("DELETEQUEUE() = %c, F=%d R=%d\n",q->queue[q->front], q->front, q->rear);
	return q->queue[q->front];
}

void current_queue(QueueType *q)
{
	int count = 0;
	printf("QUEUE = ");
	if (is_empty(q))
	{
		printf("(0)\n");
		return ;
	}
	int start = (q->front + 1) % MAX_QUEUE_SIZE;
	while (start != q->rear)
	{
		count++;
		printf("%c",q->queue[start]);
		start = (start + 1) % MAX_QUEUE_SIZE;
	}
	printf("%c (%d)\n",q->queue[start],++count);
}

Bool is_all_alpha(char *str)
{
	while (*str)
	{
		if (!isalpha(*str))
			return False;
		str++;
	}
	return True;
}

Bool is_all_digit(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return False;
		str++;
	}
	return True;
}

int main()
{
	char data[ARRAY_SIZE] = "0";
	int num;
	printf("시스템이 시작됩니다. 종료를 원할 시 -1을 입력하세요.\n");
	QueueType *queue = create();
	while (True)
	{
		printf(">>> ");
		scanf("%s",data);
		if (strcmp(data, "0") == 0)
			current_queue(queue);
		else if (strcmp(data, "-1") == 0)
			break;
		else if (is_all_alpha(data))
		{
			for (int i = 0; i < strlen(data); i++)
				enqueue(queue, data[i]);
		}
		else if (is_all_digit(data))
		{
			num = atoi(data);
			for (int i = 0; i < num; i++)
				dequeue(queue);
		}
		else
			printf("Input is invalid.\n");
	}
	free(queue);
}






