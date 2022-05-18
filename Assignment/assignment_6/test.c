#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARR_SIZE 500
typedef struct ListNode{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	struct ListNode *next;
} ListNode;

void print_data(ListNode *p)
{
	printf("%s : %s\n",p->eng, p->kor);
	if (p->next == NULL)
		printf("NULL\n");
}

void free_node(ListNode *p)
{
	if (p == NULL)
		return;
	free(p);
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* Append(ListNode *list, char word[ARR_SIZE*2])
{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	char tmp_p[ARR_SIZE];
	char tmp_prev[ARR_SIZE];
	char tmp_cur[ARR_SIZE];
	int i = 0;
	int j = 0;
	while (word[i] != ':')
		eng[j++] = word[i++];
	eng[--j] = '\0';
	j = 0;
	i++;
	while (word[i] != '\n' && word[i])
		kor[j++] = word[++i];
	kor[--j] = '\0';
	if (list == NULL)
	{
		list = (ListNode *)malloc(sizeof(ListNode));
		strcpy(list->eng,eng);
		strcpy(list->kor,kor);
		list->next = NULL;
		return list;
	}
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	strcpy(p->eng,eng);
	strcpy(p->kor,kor);

	ListNode *prev = list;
	ListNode *cur = list->next;
	while (prev)
	{
		strcpy(tmp_p, p->eng);
		strcpy(tmp_prev, prev->eng);
		int count = 0;
		while (tmp_p[count]) {
        		if (isupper(tmp_p[count])){
            			tmp_p[count] = tolower(tmp_p[count]);
        		}
			count++;
		}
		count = 0;
		while (tmp_prev[count]) {
        		if (isupper(tmp_prev[count])){
            			tmp_prev[count] = tolower(tmp_prev[count]);
        		}
			count++;
		}
		if (cur == NULL)
		{
			if (strcmp(tmp_p, tmp_prev) > 0)
			{
				prev->next = p;
				p->next = cur;
				break;
			}
			else
			{
				p->next = prev;
				list = p;
				break;
			}
		}
		strcpy(tmp_cur, cur->eng);
		count = 0;
		while (tmp_cur[count]) {
        		if (isupper(tmp_cur[count])){
            			tmp_cur[count] = tolower(tmp_cur[count]);
        		}
			count++;
		}
		if (strcmp(tmp_p, tmp_prev) > 0 && strcmp(tmp_p, tmp_cur) > 0)
		{
			prev = prev->next;
			cur = cur->next;
			continue;
		}
		else if (strcmp(tmp_p, tmp_prev) > 0)
		{
			prev->next = p;
			p->next = cur;
			break;
		}
		else
		{
			p->next = prev;
			list = p;
			break;
		}
	}
	return list;
}

void Traverse(ListNode *list, void (*fp)(ListNode *))
{
	if (list == NULL)
	{
		printf("List is Empty.\n");
		return ;
	}
	ListNode *tmp = list;
	while (tmp)
	{
		tmp = list->next;
		fp(list);
		list = tmp;
	}
}

int main()
{
	ListNode *head = NULL;
	head = Append(head, "Abc : 안");
	head = Append(head, "ac : 녕");
	head = Append(head, "Adc : 하");
	Traverse(head, print_data);
	Traverse(head, free_node);
	return 0;
}
