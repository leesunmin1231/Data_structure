#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_SIZE 500

struct _bucket* hashTable = NULL; 
int BUCKET_SIZE = 1000; // 버켓의 총 길이

typedef struct _node {
    int key;
    char eng[ARR_SIZE];
    char kor[ARR_SIZE];
    struct _node* next;
} Node;


typedef struct _bucket{
    struct _node* head; 
    int count;
} Bucket;

int getKey(char eng[ARR_SIZE])
{
	int key = (strlen(eng) * (eng[0] - 'A')) % BUCKET_SIZE;
	return key;
}


Node *createNode(char word[ARR_SIZE]){
    	Node* node;
    	node = (Node *)malloc(sizeof(Node));
    	if (node == NULL)
		return 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < ARR_SIZE; i++)
	{
		node->eng[i] = '\0';
		node->kor[i] = '\0';
	}
	i = 0;
	while (word[i] != ':')
		node->eng[j++] = word[i++];
	node->eng[--j] = '\0';
	j = 0;
	i++;
	while (word[i] != '\n' && word[i])
		node->kor[j++] = word[++i];
	node->kor[--j] = '\0';
    	node->key = getKey(node->eng);
    	node->next = NULL;
    	return node;
}

void add(char word[ARR_SIZE]){
    Node* newNode = createNode(word);
    int hashIndex = newNode->key;
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode;
    }
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

void search(char eng[ARR_SIZE]){
    int hashIndex = getKey(eng);
    Node* node = hashTable[hashIndex].head;
    int flag = 0;
    int compare = 0;
    while (node != NULL)
    {
        if (strcmp(node->eng,eng) == 0){
            flag = 1;
            break;
        }
	compare++;
        node = node->next;
    }
    if (flag == 1){
        printf("(%d회 검색)  %s\n", compare, node->kor);
    }
    else{
        printf("\n 해당 단어가 존재 하지 않습니다. \n");
    }
}

void free_hash()
{
	Node *tmp;
	for (int i = 0; i < BUCKET_SIZE; i++)
	{
		Node* node = hashTable[i].head;
		while (node!=NULL)
		{
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
	free(hashTable);
}

void print_hash()
{
	Node *tmp;
	for (int i = 0; i < BUCKET_SIZE; i++)
	{
		Node *node = hashTable[i].head;
		while(node != NULL)
		{
			printf("%s : %s\n",node->eng, node->kor);
			node = node->next;
		}
	}
}

	

int main(void)
{
	hashTable = (Bucket *)malloc(BUCKET_SIZE * sizeof(Bucket));
	char buffer[ARR_SIZE];
	FILE *fp = fopen("randdict_utf8.TXT", "r");
	int i = 0;
	while (i < ARR_SIZE)
		buffer[i++] = '\0';
	while (!feof(fp))
	{
		fgets(buffer, sizeof(buffer), fp);
		if (feof(fp)) break;
		fflush(fp);
		add(buffer);
		i++;
	}
	fclose(fp);
	//print_hash();
	printf("해싱 테이블이 완성되었습니다.\n");
	char word[ARR_SIZE];
	int j = 0;
	while (1)
	{
		int level = 0;
		printf("단어를 입력하세요 ");
		scanf("%s",word);
		if (strcmp(word,"0") == 0)
			break;
		search(word);
	}
	free_hash();
}
