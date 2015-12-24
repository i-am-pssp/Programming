#include<stdio.h>
#include<stdlib.h>
typedef struct verteex
{
    int no;
    char col;
} vertex;
typedef struct node
{
    int data;
    struct node *next;
} node;
typedef struct pair
{
    int p,q;
}pair;
void getadjlist(int n,int adj[100][100],node *adjlist[])
{
    int i,j,k;
    for(i=0; i<n; i++)
    {
        node *head;
        head=(node *)malloc(sizeof(node));
        head->data=i;
        head->next=NULL;
        for(k=0; k<i; k++)
        {
            if(adj[k][i-1]==1)
            {    node *temp;
                temp=(node *)malloc(sizeof(node));
                temp->data=k;
                temp->next=NULL;
                node *ref=head;
                while(ref->next!=NULL)
                    ref=ref->next;
                ref->next=temp;
            }
        }
        for(j=i; j<(n-1); j++)
        {
            if(adj[i][j]==1)
            {
                node *temp;
                temp=(node *)malloc(sizeof(node));
                temp->data=j+1;
                temp->next=NULL;
                node *ref=head;
                while(ref->next!=NULL)
                    ref=ref->next;
                ref->next=temp;
            }
        }
        head=head->next;
        adjlist[i]=head;
    }
}
void visit(vertex v[],int i,node *adjlist[],int *sum)
{
    node *ref;
    v[i].col='g';
    (*sum)++;
    printf("%d ",v[i].no);

    ref=adjlist[v[i].no];
    while(ref!=NULL)
    {
        if(v[ref->data].col=='w')
        {
            visit(v,ref->data,adjlist,sum);
        }
        ref=ref->next;
    }
    v[i].col='b';
}
int  lcsize(int n,node *adjlist[],int *x)
{
    vertex v[n];
    int i,count[n],cnt=0,max,*sum;
    for(i=0; i<n; i++)
        count[i]=0;
    for(i=0; i<n; i++)
    {
        v[i].no=i;
        v[i].col='w';
    }
    cnt=0;
    for(i=0; i<n; i++)
    {

        sum=(int *)malloc(sizeof(int));
        *sum=0;
        if(v[i].col=='w')
        {
            cnt++;
            (*x)++;
            printf("component %d : ",cnt);
            visit(v,i,adjlist,sum);
            count[i]=*sum;
            printf("\n");
        }

    }

    max=count[0];
    for(i=0; i<n; i++)
    {
        if(count[i]>=max)
            max=count[i];
    }

    return max;
}
void bnefind(int n,int adj[100][100])
{
    int i,j,k=0,max,x;
    node *graph[n],*head;
    pair heads[n];
    printf("/*this is not included in output\n");
for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {

            if(adj[i][j]==1)
            {
                x=0;
                adj[i][j]=0;
                getadjlist(n,adj,graph);
               max=lcsize(n,graph,&x);
                if(x!=1)
                {
                    heads[k].p=i;
                    heads[k].q=j+1;
                    k++;

                }
                adj[i][j]=1;
            }
        }
    }
    printf("*/\n");
    for(i=0;i<k;i++)
    printf("(%d ,%d ) is a bottleneck edge\n",heads[i].p,heads[i].q) ;
}
int main()
{
    int n,m,i,j,k,adj[100][100],size,*x;
    printf("number of vertices =");
    scanf("%d",&n);
    node *adjlist[n],*head;
    printf("+++reading adjacency matrix\n");
    for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {
            scanf("%d",&adj[i][j]);
        }
    }
    for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {
            printf("%d\t",adj[i][j]);
        }
        printf("\n");
        for(k=0; k<=i; k++)
            printf("\t");
    }
    printf("\n+++converting into adjacency list\n");
    getadjlist(n,adj,adjlist);
    for(i=0; i<n; i++)
    {
        printf("neighbours of %d : ",i);
        head=adjlist[i];
        while(head!=NULL)
        {
            printf("%d  ",head->data);
            head=head->next;
        }
        printf("\n");
    }

    x=(int *)malloc(sizeof(int));
    *x=0;
    printf("+++finding the largest component size\n");
    size=lcsize(n,adjlist,x);
    printf("\nthe largest component has %d nodes\n",size);
    printf("+++ Finding bottleneck edges (Inefficient)\n");
    bnefind(n,adj);
    printf("+++ Finding bottleneck edges (Efficient)\n");
    bnefindfast(n);
}
