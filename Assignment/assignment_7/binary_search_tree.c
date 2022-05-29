#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_SIZE 500

typedef struct _node{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	struct _node * right;
	struct _node * left;
} Node;

int Tree_size = 0;

Node *Create_node(char word[ARR_SIZE]) {
   	Node *node = (Node *)malloc(sizeof(Node));
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
   	node->right = NULL;
    	node->left = NULL;
    	return node;
}

void Insert(Node **tree, char word[ARR_SIZE])
{
	if (*tree == NULL)
	{
		*tree = Create_node(word);
		return;
	}
	Node *parent = NULL;
	Node *tmp = *tree;
	Node *newNode = Create_node(word); 
	while (tmp)
	{
		parent = tmp;
		if (strcmp(newNode->eng,tmp->eng) < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	if (strcmp(newNode->eng, parent->eng) < 0)
		parent->left = newNode;
	else
		parent->right = newNode;
}


void Inorder(Node *tree) {
    if (tree)
    {
       	Inorder(tree->left);
       	printf("%s : ", tree->eng);
       	printf("%s\n", tree->kor);
       	Inorder(tree->right);
    }
}

Node *Search_word(Node *tree, char eng[ARR_SIZE], int *count)
{
	(*count)++;
	if (tree == NULL)
		return 0;
	if (strcmp(eng, tree->eng) == 0)
		return tree;
	if (strcmp(eng, tree->eng) < 0)
		return Search_word(tree->left, eng, count);
	else
		return Search_word(tree->right, eng, count);
}

void free_tree(Node *tree)
{

	if (tree)
	{
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree);
	}
}

int get_height(Node *tree)
{
	int height = 0;
	if (tree)
	{
		if (tree->left == NULL && tree->right == NULL)
			height = 1;
		else
		{
			int le = get_height(tree->left);
			int ri = get_height(tree->right);
			if (le >= ri)
				height = le + 1;
			else
				height = ri + 1;
		}
	}
	return height;
}

void get_tree_size(Node *tree)
{
	if (tree)
	{
		Tree_size++;
		get_tree_size(tree->left);
		get_tree_size(tree->right);
	}
}

int main(void)
{
	Node *tree = NULL;
	char buffer[ARR_SIZE];
	clock_t start, end;
	double search_time[ARR_SIZE];
	FILE *fp = fopen("randdict_utf8.TXT", "r");
	int i = 0;
	while (i < ARR_SIZE)
		buffer[i++] = '\0';
	while (!feof(fp))
	{
		fgets(buffer, sizeof(buffer), fp);
		if (feof(fp)) break;
		fflush(fp);
		Insert(&tree, buffer);
		i++;
	}
	fclose(fp);
	get_tree_size(tree);
	printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n",Tree_size);
	printf("A 트리의 전체 높이는 %d 입니다. A트리의 노드 수는 %d개 입니다.\n", get_height(tree), Tree_size);
	char word[ARR_SIZE];
	int j = 0;
	while (1)
	{
		int level = 0;
		printf("단어를 입력하세요 ");
		scanf("%s",word);
		if (strcmp(word,"0") == 0)
			break;
		start = clock();
		Node *to_find = Search_word(tree, word, &level);
		end = clock();
		if (to_find == NULL)
			printf("찾는 단어가 없습니다.\n");
		else if (to_find != NULL)
			printf("(레벨 : %d) %s\n",level, to_find->kor);
		double runtime = (double)(end - start);
		search_time[j++] = runtime;
	}
	for (int k = 0; k < j; k++)
		printf("search time: %.0lf ms\n", search_time[k]);
	free_tree(tree);
}
