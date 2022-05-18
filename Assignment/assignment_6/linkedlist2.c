#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타 입
	element data;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 노드 pre 뒤에 새로운 노드 삽입
void insert(ListNode** phead, ListNode* pre, element value)
{
	ListNode* new_node = malloc(sizeof(ListNode));	//(1)

	if (new_node == NULL)
		return;  // FAIL

	new_node->data = value;		//(2)

	if (*phead == NULL) {	// 공백리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (pre == NULL) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p 다음에 삽입
		new_node->link = pre->link;
		pre->link = new_node;
	}
}

// pre가 가리키는 노드의 다음 노드를 삭제한다. 
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

// 테스트 프로그램
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
