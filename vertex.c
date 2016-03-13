#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;

typedef struct {
        int top;
        int data[100];
} ver;

typedef struct
{
	int high;
	int *a;
} queue;

void BFS(ver *Ver, int *d, char *color, int v) 
{
	int t=0,i,u;
	queue Queue;
	Queue.a=(int*)malloc(n*sizeof(int));
	Queue.high=0;
	memset(color, 0, n*sizeof(char));
	color[v]=-1;
	d[v]=0;
	Queue.a[Queue.high]=v;
	Queue.high++;
	while(t!=Queue.high)
	{
		u=Queue.a[t];
		t++;
		for(i=0; i<Ver[u].top; i++)
		{
			if(color[Ver[u].data[i]]==0)
			{
				color[Ver[u].data[i]]=-1;
				d[Ver[u].data[i]]=d[u]+1;
				Queue.a[Queue.high]=Ver[u].data[i];
				Queue.high++;
			}
		}
		color[u]=1;
	}
	free(Queue.a);
} 

int main() 
{
	int a,b,ve,n1,n2,i,j,z=0,k;
	scanf("%i", &n);
	scanf("%i", &n1);
	ver *Ver=calloc(n, sizeof(ver));
	char *color=malloc(n * sizeof(char));
	for (i=0;i<n1; i++)
	{
		scanf("%i %i",&a,&b);
		Ver[a].data[Ver[a].top]=b;
		Ver[a].top++;
		Ver[b].data[Ver[b].top] = a;
		Ver[b].top++;
	}
	scanf("%i", &n2);
	int **d=malloc(n2 * sizeof(int*));
	for (i = 0; i < n2; i++)
	{
		d[i]=malloc(n*sizeof(int));
		scanf("%i", &ve);
		for (j=0; j<n; j++)
  			d[i][j]=-1;
		BFS(Ver, d[i], color, ve);
	}

	for(j=0; j<n;j++)
	{
		k=0;
		for(i=1; i<n2; i++)
			if(d[i][j]==-1||d[i][j]!=d[i-1][j])
			{
				k=1;
				break;
			}
		if(k==0)
		{
			printf("%i ", j);
			z=1;
		}
	}
	if(z==0)
		printf("-");
	printf("\n");
	for (i=0; i<n2; i++) 
		free(d[i]);
	free(Ver);
	free(color);
	free(d);
	return 0;
}  
