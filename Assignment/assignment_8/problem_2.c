#include <stdio.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7
#define INF 1000

int weight[MAX_VERTICES][MAX_VERTICES] = {
	{ 0, 4, 8, INF, INF, INF, 10 },
	{ 4, 0, 2, 5, 11, INF, INF},
	{ 8, 2, 0, INF, 9, 4, 5},
	{ INF, 5, INF, 0, 7, INF, INF},
	{ INF, 11, 9, 7, 0, 2, 8},
	{ INF, INF, 4, INF, 2, 0, INF},
	{ 10, INF, 5, INF, 8, INF, 0}};
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];
int check[MAX_VERTICES];

void path_init(int path[][MAX_VERTICES]){ 
	int i,j; 
	for(i=0;i<MAX_VERTICES;i++)  
		for(j=0;j<MAX_VERTICES;j++)   
			path[i][j] = INF;
}

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
	{
		if (distance[i] < min && ! found[i]){
			min = distance[i];
			minpos=i;
		}
	}
	return minpos;
}

void shortest_path(int start, int n)
{
	int i, j, u, w;
	for (i = 0; i < n; i++)
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i] = 1;
		path[i][0] = start;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 0; i<n-2; i++)
	{
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
		{
			if(!found[w])
			{
				if (distance[u]+weight[u][w] < distance[w])
				{
					if (i==0)
					{
						path[w][check[w]] = u;
						check[w]++;
					}
					else{
						for(j = 0; j<(check[u]+1); j++)
						{
							path[w][j] = path[u][j];
							path[w][j+1] = u;
							check[w]++;
						}
					}
					distance[w] = distance[u] + weight[u][w];
				}
			}
		}
	}
}

int main()
{
	int i, j, start, end;

	path_init(path);
	printf("시작점?: ");
	scanf("%d", &start);
	printf("도착점?: ");
	scanf("%d", &end);
	shortest_path(start, MAX_VERTICES);
	printf("경로는 ");
	for (j = 0; j < MAX_VERTICES; j++){
		if(path[end][j]!=INF){
			printf("%d-",path[end][j]);
		}
	}
	printf("%d\n",end);
	printf("거리는 %d\n",distance[end]);  
}
