#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ ��
	element data;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ��� pre �ڿ� ���ο� ��� ����
void insert(ListNode** phead, ListNode* pre, element value)
{
	ListNode* new_node = malloc(sizeof(ListNode));	//(1)

	if (new_node == NULL)
		return;  // FAIL

	new_node->data = value;		//(2)

	if (*phead == NULL) {	// ���鸮��Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (pre == NULL) { // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p ������ ����
		new_node->link = pre->link;
		pre->link = new_node;
	}
}

// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
void delete(ListNode** phead, ListNode* pre)
{
	ListNode* removed;

	if (pre == NULL) {
		removed = (*phead);
		*phead = (*phead)->link;
	}
	else {
		removed = pre->link;
		pre->link = removed->link;
	}

	free(removed);			// (3)

}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

// �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;

	for (int i = 0; i < 5; i++) {
		insert(&head, head, i);
		print_list(head);
	}


	for (int i = 0; i < 4; i++) {
		delete(&head, head);
		print_list(head);
	}

	delete(&head, NULL);
	print_list(head);

	return 0;
}
