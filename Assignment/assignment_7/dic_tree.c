#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_SIZE 200

typedef struct _node{
	char eng[ARR_SIZE];
	char kor[ARR_SIZE];
	struct _node * right;
	struct _node * left;
} Node;

Node *Create_node(char word[ARR_SIZE]) {
   	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL)
		return 0;
	int i = 0;
	int j = 0;
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

Node *Search_word(Node *tree, char eng[ARR_SIZE])
{
	if (tree == NULL || strcmp(eng, tree->eng) == 0)
		return tree;
	if (strcmp(eng, tree->eng) < 0)
		return Search(tree->left, eng);
	else
		return Search(tree->right, eng);
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

int main(void)
{
    Node *tree = NULL;
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
		Insert(&tree, buffer);
		i++;
	}
	end = clock();
	double insert_time = (double)(end - start);
	fclose(fp);
   	Inorder(tree);
	printf("\n");
	printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n",i);
	char word[ARR_SIZE];
	int j = 0;
	while (1)
	{
		printf(">> ");
		scanf("%s",word);
		if (strcmp(word,"0") == 0)
			break;
		start = clock();
		Search_word(tree, word);
		end = clock();
		double runtime = (double)(end - start);
		search_time[j++] = runtime;
	}
	//for (int k = 0; k < j; k++)
	//	printf("search time: %.0lf ms\n", search_time[k]);
	//printf("insert time: %.0lf ms\n", insert_time);
	free_tree(tree);
}
