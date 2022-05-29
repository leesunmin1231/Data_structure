#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define ARR_SIZE 500
typedef struct ListNode{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	struct ListNode *next;
	struct ListNode *prev;
} ListNode;

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->next)
		printf("%s : %s\n",p->eng, p->kor);
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

int is_tail(char alpha)
{
	if ((alpha > 'm' && alpha <= 'z') || (alpha > 'M' && alpha <= 'Z'))
		return 1;
	return 0;
}

void insert_tail(ListNode **head, ListNode **tail, ListNode *p)
{
	char tmp_p[ARR_SIZE];
	char tmp_cur[ARR_SIZE];
	ListNode *cur = *tail;
	while (cur)
	{
		strcpy(tmp_p, p->eng);
		strcpy(tmp_cur, cur->eng);
		int count = 0;
		while (tmp_p[count]) {
        		if (isupper(tmp_p[count])){
            			tmp_p[count] = tolower(tmp_p[count]);
        		}
			count++;
		}
		count = 0;
		while (tmp_cur[count]) {
        		if (isupper(tmp_cur[count])){
            			tmp_cur[count] = tolower(tmp_cur[count]);
        		}
			count++;
		}
		if (cur->next == NULL)
		{
			if (strcmp(tmp_p, tmp_cur) > 0)
			{
				cur->next = p;
				p->next = NULL;
				p->prev = cur;
				*tail = p;
				return;
			}
		}

		if (cur->prev == NULL || !is_tail(cur->prev->eng[0]))
		{
			if (strcmp(tmp_p, tmp_cur) < 0)
			{
				p->next = cur;
				p->prev = cur->prev;
				cur->prev = p;
				if(cur->prev == NULL)
					*head = p;
				return;
			}
		}
		if (strcmp(tmp_p, tmp_cur) < 0)
		{
			cur = cur->prev;
			continue;
		}
		else
		{
			cur->next->prev = p;
			p->prev = cur;
			p->next = cur->next;
			cur->next = p;
			return;
		}
	}
}

void insert_front(ListNode **head, ListNode **tail, ListNode *p)
{
	char tmp_p[ARR_SIZE];
	char tmp_cur[ARR_SIZE];
	ListNode *cur = *head;
	while (cur)
	{
		strcpy(tmp_p, p->eng);
		strcpy(tmp_cur, cur->eng);
		int count = 0;
		while (tmp_p[count]) {
        		if (isupper(tmp_p[count])){
            			tmp_p[count] = tolower(tmp_p[count]);
        		}
			count++;
		}
		count = 0;
		while (tmp_cur[count]) {
        		if (isupper(tmp_cur[count])){
            			tmp_cur[count] = tolower(tmp_cur[count]);
        		}
			count++;
		}
		if (cur->next == NULL || is_tail(cur->next->eng[0]))
		{
			if (strcmp(tmp_p, tmp_cur) > 0)
			{
				p->next = cur->next;
				p->prev = cur;
				cur->next = p;
				if (cur->next == NULL)
					*tail = p;
				return;
			}
		}

		if (cur->prev == NULL)
		{
			if (strcmp(tmp_p, tmp_cur) < 0)
			{
				p->next = cur;
				p->prev = NULL;
				cur->prev = p;
				*head = p;
				return;
			}
		}
		if (strcmp(tmp_p, tmp_cur) > 0)
		{
			cur = cur->next;
			continue;
		}
		else
		{
			cur->prev->next = p;
			p->prev = cur->prev;
			p->next = cur;
			cur->prev = p;
			return;
		}
	}
}

void Append(ListNode **head, ListNode **tail, char word[ARR_SIZE*2])
{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	char tmp_p[ARR_SIZE];
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

	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	strcpy(p->eng,eng);
	strcpy(p->kor,kor);

	if (*head == NULL)
	{
		p->next = NULL;
		p->prev = NULL;
		*head = p;
		*tail = p;
		return;
	}
	if (is_tail(p->eng[0]))
		insert_tail(head, tail, p);
	else
		insert_front(head, tail, p);
}

void Traverse(ListNode **list, void (*fp)(ListNode *))
{
	if (*list == NULL)
	{
		printf("List is Empty.\n");
		return ;
	}
	ListNode *tmp = *list;
	ListNode *next;
	while (tmp)
	{
		next = tmp->next;
		fp(tmp);
		tmp = next;
	}
}

void Search_word(ListNode **head, ListNode **tail, char word[ARR_SIZE], int count)
{
	if (is_tail(word[0]))
	{
		ListNode *dic = *tail;
		while (dic)
		{
			if (!is_tail(dic->eng[0]))
				break;
			if (strcmp(dic->eng, word) == 0)
			{
				printf("%s\n",dic->kor);
				return;
			}
			dic = dic->prev;
		}
	}
	else
	{
		ListNode *dic = *head;
		while (dic)
		{
			if (is_tail(dic->eng[0]))
				break;
			if (strcmp(dic->eng, word) == 0)
			{
				printf("%s\n",dic->kor);
				return;
			}
			dic = dic->next;

		}
	}
	printf("찾을 수 없는 단어입니다. 뜻을 추가하세요. (추가하지 않으려면 '0' 을 입력하세요.)\n");
	char mean[ARR_SIZE];
	char total[ARR_SIZE*2];
	printf("> ");
	scanf("%s",mean);
	if (strcmp(mean, "0") == 0)
	{
		printf("추가하지 않습니다.\n");
		return;
	}
	strcpy(total,word);
	strcat(total, " : ");
	strcat(total,mean);
	Append(head, tail, total);
	count++;
	printf("%s %s 가 추가되었습니다.(총 %d개 단어)\n",word,mean, count);
	return;
}


int main(void)
{
	ListNode *head = NULL;
	ListNode *tail = NULL;
	char buffer[ARR_SIZE];
	clock_t start, end;
	double search_time[ARR_SIZE];
	FILE *fp = fopen("randdict_utf8.TXT", "r");
	int i = 0;
	start = clock();
	while (!feof(fp))
	{
		fgets(buffer, sizeof(buffer), fp);
		if (feof(fp)) break;
		Append(&head, &tail, buffer);
		i++;
	}
	end = clock();
	double insert_time = (double)(end - start);
	fclose(fp);
	print_list(head);
	char word[ARR_SIZE];
	int j = 0;
	while (1)
	{
		printf(">> ");
		scanf("%s",word);
		if (strcmp(word,"0") == 0)
			break;
		start = clock();
		Search_word(&head, &tail, word, i);
		end = clock();
		double runtime = (double)(end - start);
		search_time[j++] = runtime;
	}
	//for (int k = 0; k < j; k++)
	//	printf("search time: %.0lf ms\n", search_time[k]);
	//printf("insert time: %.0lf ms\n", insert_time);
	Traverse(&head, free_node);
	return 0;
}
