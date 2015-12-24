#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} node;
typedef struct tree
{
    int r;
    struct tree *p;
} tree;
typedef struct edge
{
    int u,v,w;
} edge;
typedef struct key
{
    int id,wt,pos;
} key;
void getadjlist(int n,int **adj,node *adjlist[])
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
            if(adj[k][i-1]!=0)
            {
                node *temp;
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
            if(adj[i][j]!=0)
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
void merge(edge *e,int l,int m,int r)
{
    if(l==r)
        return ;
    int x,y,k=l,i,l1=0,l2=0;
    x=m-l+1;
    y=r-m;
    edge p[x],q[y];
    for(i=0; i<x; i++)
        p[i]=e[l+i];
    for(i=0; i<y; i++)
        q[i]=e[m+i+1];
    while(l1<x && l2<y)
    {
        if(p[l1].w<=q[l2].w)
        {
            e[k]=p[l1];
            l1++;
            k++;

        }
        else
        {
            e[k]=q[l2];
            l2++;
            k++;
        }
    }
    while(l1<x)
    {
        e[k]=p[l1];
        l1++;
        k++;
    }
    while(l2<y)
    {
        e[k]=q[l2];
        l2++;
        k++;
    }

}
void mergesort(edge *e,int l,int r)
{
    if(l<r)
    {
        int m;
        m=(l+r)/2;
        mergesort(e,l,m);
        mergesort(e,m+1,r);
        merge(e,l,m,r);
    }
}
void makeset(tree **t,int i)
{
    t[i]->r=0;
    t[i]->p=t[i];
}
tree *findset(tree *t)
{
    if(t->p!=t)
        t->p=findset(t->p);
    return t->p;
}
void setunion(tree *t1,tree *t2)
{
    tree *root1,*root2;
    root1=findset(t1);
    root2=findset(t2);
    if(root1->r>root2->r)
        root2->p=root1;
    else
    {
        root1->p=root2;
        if(root1->r==root2->r)
            root2->r++;
    }
}
void kruskal(int **w,int n)
{
    tree **t;
    int k=0,i,j,weight=0;
    edge *e;
    e=(edge *)malloc((n*n)*sizeof(edge));
    t=(tree **)malloc(n*sizeof(tree *));
    for(i=0; i<n; i++)
        t[i]=(tree *)malloc(sizeof(tree));
    for(i=0; i<n; i++)
        makeset(t,i);
    for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {
            if(w[i][j]!=0)
            {
                e[k].w=w[i][j];
                e[k].u=i;
                e[k].v=j+1;
                k++;
            }
        }
    }
    mergesort(e,0,k-1);
    printf("edges in sorted order are\n");
    for(i=0; i<k; i++)
        printf("%d ",e[i].w);
    printf("\nthe edges of the spanning tree are");
    for(i=0; i<k; i++)
    {
        if(findset(t[e[i].u])!=findset(t[e[i].v]))
        {
            weight+=e[i].w;
            printf("(%d,%d)",e[i].u,e[i].v);
            setunion(t[e[i].u],t[e[i].v]);
        }
    }
    printf("\nminimum weight of the spanning tree=%d\n",weight);
}
void minheapify(key *a,int i,int n)
{
    int l,r,small,temp;
    l=2*i+1;
    r=2*i+2;
    if(l<n && a[l].wt<a[i].wt)
        small=l;
    else
        small=i;
    if(r<n && a[r].wt<a[small].wt)
        small=r;
    if(small!=i)
    {
        temp=a[small].wt;
        a[small].wt=a[i].wt;
        a[i].wt=temp;
        minheapify(a,small,n);
    }
}
void buildminheap(key *a,int n)
{
    int i;
    for(i=n/2-1; i>=0; i--)
        minheapify(a,i,n);
}
key  deletemin(key *a, int n)
{
    int ref,i,child;
    key min,last;
    min=a[0];
    ref=a[n-1].wt;
    last=a[n-1];
    n--;
    for(i=0; i<n; i=child)
    {
        child=2*i+1;
        if(child!=(n-1) && a[child+1].wt<a[child].wt)
            child++;
        if(a[child].wt<ref)
        {
            a[i]=a[child];
            a[i].pos=a[child].pos;
            a[child]=last;
            a[child].pos=last.pos;
        }
        else
          {
               a[i]=last;
               a[i].pos=last.pos;
               break;
          }
    }

    return min;
}
void adjust(key *a,int i)
{
    key temp;
    while(i>0)
    {
        if(a[i].wt<=a[(i-1)/2].wt)
        {
            temp=a[i];
            temp.pos=a[i].pos;
            a[i]=a[(i-1)/2];
            a[i].pos=a[(i-1)/2].pos;
            a[(i-1)/2]=temp;
            a[(i-1)/2].pos=temp.pos;
            i=(i-1)/2;
        }
        else
            break;
    }
}
void prim(int **w,int n,int r)
{
    key *a,u;
    int *pi,i,j,v,copy=n,weight=0,*check;
    check=(int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
        check[i]=1;
    a=(key *)malloc((n+1)*sizeof(key));
    pi=(int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    {
        a[i].wt=100;
        a[i].id=i;
        a[i].pos=i;
        pi[i]=-1;
    }
    a[r].wt=0;
    buildminheap(a,n);
    while(n>=1)
    {
        printf("n=%d\n",n);
        for(i=0; i<n; i++)
        {
            printf("(%d,%d) ",a[i].wt,a[i].id);
        }
        u= deletemin(a,n);
        n--;
        check[u.id]=0;
        weight+=u.wt;
if(pi[u.id]!=-1)
            printf("\n(%d,%d) weight=%d\n",pi[u.id],u.id,weight);
            for( j=u.id; j<(copy-1); j++)
        {
            if(w[u.id][j]!=0)
            {
                printf("w[%d][%d]=%d\n",u.id,j,w[u.id][j]);
                if(a[j+1].pos<n && check[j+1]==1 && w[u.id][j]<a[j+1].wt)
                {
                    pi[j+1]=u.id;
                    a[j+1].wt=w[u.id][j];

                    adjust(a,a[j+1].pos);
                    for(i=0; i<n; i++)
                    {
                        printf("(%d,%d) ",a[i].wt,a[i].id);
                    }
                    printf("\n");
                }
            }
        }

    }
    printf("\nminimum weight of the spanning tree=%d\n",weight);
}
int main()
{
    int n,m,i,j,k,adj[100][100],**w,size,*x,r;
    printf("number of vertices =");
    scanf("%d",&n);
    printf("n=%d\n",n);
    w=(int **)malloc(n*sizeof(int *));
    for(i=0; i<n; i++)
        w[i]=(int *)malloc(n*sizeof(int));
    node *adjlist[n],*head;
    printf("+++reading weight matrix\n");
    for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {
            scanf("%d",&w[i][j]);
        }
    }
    for(i=0; i<(n-1); i++)
    {
        for(j=i; j<(n-1); j++)
        {
            printf("%d\t",w[i][j]);
        }
        printf("\n");
        for(k=0; k<=i; k++)
            printf("\t");
    }
    printf("\n+++converting into adjacency list\n");
    getadjlist(n,w,adjlist);
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

    kruskal(w,n);
    printf("enter reference vertex\n");
    scanf("%d",&r);
    prim(w,n,r);
}

