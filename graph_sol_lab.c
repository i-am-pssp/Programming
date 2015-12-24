#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NIL -1
#define INFINITE 999999
int count,comp;
typedef struct graph
{
    int neigh;
    struct graph *next;
} node;

typedef struct ordered
{
    int d,e;
} pairs;
node** adjacencylist(node **graph,int **adj,int n)
{
    int i,j,m=0,u,v,check=0;
    node *p,*q;
    graph=(node**)malloc(n*sizeof(node*));
    for(i=0; i<n; i++)
    {
        graph[i]=(node*)malloc(sizeof(node));
        graph[i]->next=NULL;
    }
    for(i=0; i<n; i++)
    {
        for(j=i; j<n; j++)
        {
            if(adj[i][j])
            {
                p=graph[i];
                if(p->next==NULL)
                {
                    p->next=(node*)malloc(sizeof(node));
                    p=p->next;
                    p->next=NULL;
                    p->neigh=j;
                }
                else
                {
                    q=p;
                    p=p->next;
                    while(p->neigh<j)
                    {
                        q=p;
                        p=p->next;
                        if(p==NULL)
                            break;
                    }
                    q->next=(node*)malloc(sizeof(node));
                    q->next->neigh=j;
                    q->next->next=p;
                }
                if(i==j)
                    continue;
                p=graph[j];
                if(p->next==NULL)
                {
                    p->next=(node*)malloc(sizeof(node));
                    p=p->next;
                    p->next=NULL;
                    p->neigh=i;
                }
                else
                {
                    q=p;
                    p=p->next;
                    while(p->neigh>i)
                    {
                        q=p;
                        p=p->next;
                        if(p==NULL)
                            break;
                    }
                    q->next=(node*)malloc(sizeof(node));
                    q->next->neigh=i;
                    q->next->next=p;
                }
            }
        }
    }

    return graph;
}
void dfs(node **graph,int u,int *visited,int *d,int *par)
{
    node *p;
    int v;
    p=graph[u];
    p=p->next;
    while(p!=NULL)
    {
        v=p->neigh;
        if(visited[v]==0)
        {
            printf("%d ",v);
            visited[v]=1;
            d[v]=d[u]+1;
            par[v]=u;
            dfs(graph,v,visited,d,par);
            count++;
        }
        p=p->next;
    }
    return;
}
int lcsize(node **graph,int n)
{
    int *visited,*par,*d,max,i,j;
    visited=(int*)malloc(n*sizeof(int));
    par=(int*)malloc(n*sizeof(int));
    d=(int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
        visited[i]=0;
    max=0;
    for(i=0; i<n; i++)
    {
        if(visited[i]==0)
        {
            comp++;
            printf("Component %d: ",comp);
            printf("%d ",i);
            visited[i]=1;
            d[i]=0;
            par[i]=-1;
            count=1;
            dfs(graph,i,visited,d,par);
            if(count>max)
                max=count;
        }
    }
    return max;
}
void bnefind(node **graph,int **adj,int n)
{
    int i,j,x,k=0;
    pairs head[100];
    printf("\n/*\nThese are not included in the output");
    for(i=0; i<n; i++)
    {
        for(j=i; j<n; j++)
        {
            if(adj[i][j]==1)
            {
                adj[i][j]=adj[j][i]=0;
                graph=adjacencylist(graph,adj,n);
                printf("\n");
                comp=0;
                x=lcsize(graph,n);
                if(comp>1)
                {
                    head[k].d=i;
                    head[k].e=j;
                    k++;
                }
                adj[i][j]=adj[j][i]=1;
                graph=adjacencylist(graph,adj,n);
            }
        }
    }
    printf("\n*/\n\n");
    printf("+++ Finding bottleneck edges (Inefficient)\n");
    for(i=0; i<k; i++)
    {
        printf("( %d , %d ) is a bottleneck edge\n",head[i].d,head[i].e);
    }
}
void dfslast(node **graph,int u,int *visited,int *num,int *min,int *parent,int *count)
{
    node *p;
    int v,i,j;
    p=graph[u];
    p=p->next;
    while(1)
    {
        v=p->neigh;
        if(visited[v]==0)
        {
            visited[v]=1;
            (*count)++;
            num[v]=(*count);
            parent[v]=u;
            dfslast(graph,v,visited,num,min,parent,count);
        }
        else
        {
            if(min[u]>num[v])
            {
                if(v!=parent[u])
                    min[u]=num[v];
            }
            if(parent[u]!=v)
            {
                if(min[u]>min[v])
                {
                    min[u]=min[v];
                }
            }
        }
        if(parent[u]!=v)
        {
            if(min[u]>min[v])
            {
                min[u]=min[v];
            }
        }
        p=p->next;
        if(p==NULL)
            break;
    }
}
void bnefindfast(node **graph,int n)
{
    int *visited,*num,*min,*parent,max,i,j,**check,count=0,u,v;
    node *p;
    check=(int**)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
        check[i]=(int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            check[i][j]=0;
        }
    }
    visited=(int*)malloc(n*sizeof(int));
    num=(int*)malloc(n*sizeof(int));
    min=(int*)malloc(n*sizeof(int));
    parent=(int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    {
        visited[i]=0;
        num[i]=min[i]=INFINITE;
        parent[i]=NIL;
    }
    visited[0]=1;
    min[0]=num[0]=0;
    dfslast(graph,0,visited,num,min,parent,&count);
    for(u=0; u<n; u++)
    {
        p=graph[u];
        p=p->next;
        while(p!=NULL)
        {
            v=p->neigh;
            if(check[u][v]==0)
            {
                if(min[v]>num[u])
                {
                    check[u][v]=check[v][u]=1;
                    printf("( %d , %d ) is a bottleneck edge\n",u,v);
                }
            }
            p=p->next;
        }
    }
}

int main()
{
    node **graph,*p;
    int n,i,j,**adj,max;
    printf("Enter the number of edges\n");
    scanf("%d",&n);
    adj=(int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++)
        adj[i]=(int*)malloc(n*sizeof(int));
    printf("+++ Reading adjacency matrix\n");
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {

            scanf("%d",&adj[i][j]);
        }
    }
    for(i=0;i<n;i++)
        adj[i][i]=0;
    printf("+++ Converting adjacency matrix to adjacency list\n");
    graph=adjacencylist(graph,adj,n);
    for(i=0; i<n; i++)
    {
        printf("Neighbors of %d : ",i);
        p=graph[i];
        p=p->next;
        while(p!=NULL)
        {
            printf("%d ",p->neigh);
            p=p->next;
        }
        printf("\n");
    }
    printf("+++ Finding the largest component size\n");
    max=lcsize(graph,n);
    printf("\nThe largest component has %d nodes\n",max);
    bnefind(graph,adj,n);
    printf("\n+++ Finding bottleneck edges (Efficient)\n");
    bnefindfast(graph,n);
}
