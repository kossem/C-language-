#include <stdio.h>
#include <stdlib.h>

struct elem
{
        int index;
	int key;
	int top;
	struct dor
	{
		struct elem *u;
		int dist;
	}data[150];
};

typedef struct
{
	struct elem **h;
	int top;
}pq;

void insert(pq *pqueue,struct elem *b)
{
	int i=pqueue->top++;
	pqueue->h[i]=b;
	while((i>0)&&(pqueue->h[(i-1)/2]->key>pqueue->h[i]->key))
	{
		struct elem*a;
		a=pqueue->h[(i-1)/2];
		pqueue->h[(i-1)/2]=pqueue->h[i];
		pqueue->h[i]=a;
		pqueue->h[i]->index=i,
		i=(i-1)/2;
	}
	pqueue->h[i]->index=i;
}

void Heapify(pq *pqueue)
{
	int i=0,left,right,j;
	struct elem*a;
	while(1)
	{
		left=2*i+1;
		right=left+1;
		j=i;
		if(left<pqueue->top)
			if(pqueue->h[i]->key>pqueue->h[left]->key)
				i=left;
		if(right<pqueue->top)
			if(pqueue->h[i]->key>pqueue->h[right]->key)
				i=right;
		if(i-j==0)
			break;
		a=pqueue->h[i];
		pqueue->h[i]=pqueue->h[j];
		pqueue->h[j]=a;
		pqueue->h[i]->index=i;
		pqueue->h[j]->index=j;
	}
	
}


struct elem* ExtractMin(pq *pqueue)
{
	struct elem *a=pqueue->h[0];
	pqueue->top--;
	if(pqueue->top!=0)
	{
		pqueue->h[0]=pqueue->h[pqueue->top];
		pqueue->h[0]->index=0;
		Heapify(pqueue);
	}
	return a;
}


void DecreaseKey(pq *pqueue,struct elem*x,int k)
{
	int i=x->index;
	x->key=k;
	pqueue->h[i]->key=k;
	while((i>0)&&(pqueue->h[(i-1)/2]->key>k))
	{
		struct elem*a;
		int z=(i-1)/2;
		a=pqueue->h[(i-1)/2];
		pqueue->h[(i-1)/2]=pqueue->h[i];
		pqueue->h[i]=a;
		pqueue->h[i]->index=i;
		i=(i-1)/2;
	}	
	pqueue->h[i]->index=i;
}
void Prim(pq *pqueue,struct elem **Ver)
{
	int k=0,i,y=0;
	struct elem *v;
	v=Ver[0];
	while(1)
	{
		v->index=-2;
		for(i=0;i<v->top;i++)
		{
			struct elem *u=v->data[i].u;
			int a=v->data[i].dist;
			if(u->index==-1)
			{
				u->key=a;
				insert(pqueue,u);
			}
			else if((u->index!=-2)&&(a<u->key))
				DecreaseKey(pqueue,u,a);
		}
		if(pqueue->top==0)
			break;
		v=ExtractMin(pqueue);
		k+=v->key;
	}
	printf("%i\n",k);
}


int main()
{
	int a,b,c,n,n1,i;
	scanf("%i",&n);
	scanf("%i",&n1);
	struct elem **Ver=calloc(n,sizeof(struct elem*));
	pq pqueue;
	pqueue.top=0;
	pqueue.h=calloc(n,sizeof(struct elem*));
	for(i=0;i<n;i++)
	{
		Ver[i]=calloc(1,sizeof(struct elem));
		Ver[i]->index=-1;
		Ver[i]->key=-11;
		Ver[i]->top=0;
	}
	for(i=0;i<n1;i++)
	{
		scanf("%i %i %i",&a,&b,&c);
		Ver[a]->data[Ver[a]->top]=(struct dor){Ver[b],c};
		Ver[a]->top++;
		Ver[b]->data[Ver[b]->top]=(struct dor){Ver[a],c};
		Ver[b]->top++;
	}
	Prim(&pqueue,Ver);
	for(i=0;i<n;i++)
		free(Ver[i]);
	free(Ver);
	free(pqueue.h);
	return 0;
}
