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

ListNode *Search_word(ListNode *dic, char word[ARR_SIZE])
{
	ListNode *head = dic;
	int count = 0;
	while (dic)
	{
		if (strcmp(dic->eng, word) == 0)
		{
			printf("%s\n",dic->kor);
			return head;
		}
		dic = dic->next;
		count++;
	}
	printf("찾을 수 없는 단어입니다. 뜻을 추가하세요. (추가하지 않으려면 '0' 을 입력하세요.)\n");
	char mean[ARR_SIZE];
	char total[ARR_SIZE*2];
	printf("> ");
	scanf("%s",mean);
	if (strcmp(mean, "0") == 0)
	{
		printf("추가하지 않습니다.\n");
		return head;
	}
	strcpy(total,word);
	strcat(total, " : ");
	strcat(total,mean);
	head = Append(head, total);
	count++;
	printf("%s %s 가 추가되었습니다.(총 %d개 단어)\n",word,mean, count);
	return head;
}


int main(void)
{
	ListNode *head = NULL;
	char buffer[ARR_SIZE];
	clock_t start, end;
	double search_time[ARR_SIZE];
	FILE *fp = fopen("randdict_utf8.TXT", "r");
	int i = 0;
	while (!feof(fp))
	{
		fgets(buffer, sizeof(buffer), fp);
		if (feof(fp)) break;
		head = Append(head, buffer);
	}
	fclose(fp);
	char word[ARR_SIZE];
	int j = 0;
	while (1)
	{
		printf(">> ");
		scanf("%s",word);
		if (strcmp(word,"0") == 0)
			break;
		start = clock();
		head = Search_word(head, word);
		end = clock();
		double runtime = (double)(end - start);
		search_time[j++] = runtime;
	}
	for (int k = 0; k < j; k++)
		printf("search time: %.0lf ms\n", search_time[k]);
	Traverse(head, free_node);
	return 0;
}
