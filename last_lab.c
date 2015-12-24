#include<stdio.h>
#include<stdlib.h>
void seqtotree(int seq[],int n)
{
    int *check,*node,*deg,i,j,k,min,ref;
    int **adj,temp1[2];

    adj=(int **)malloc(n*sizeof(int *));
    for(i=0; i<n; i++)
        adj[i]=(int *)malloc(n*sizeof(int));
    check=(int*)malloc(n*sizeof(int));
    node=(int*)malloc(n*sizeof(int));
    deg=(int*)malloc(n*sizeof(int));

    for(i=0; i<n; i++)
        deg[i]=0;
    for(i=0; i<n; i++)
        node[i]=i;
    for(i=0; i<n; i++)
        check[i]=1;
    printf("hi2\n");
    for(i=0; i<(n-2); i++)
    {
        for(k=0; k<n; k++)
        {
            ref=-1;
            if(check[k]==1)
            {
                for(j=0; j<(n-2); j++)
                {
                    if(k==seq[j])
                    {
                        ref=0;
                        break;
                    }
                }

            }
            if(ref==-1)
            {
                check[k]=0;
                deg[k]+=1;
                deg[seq[i]]+=1;
                adj[k][seq[i]]=1;
                adj[seq[i]][k]=1;
            }
        }
    }
    printf("hi3\n");
    j=0;
    for(i=0; i<n; i++)
    {
        if(check[i]==1)
        {
            temp1[j]=i;
            j++;
        }
    }
    deg[temp1[0]]+=1;
    deg[temp1[1]]+=1;
    adj[temp1[0]][temp1[1]]=1;
    adj[temp1[1]][temp1[0]]=1;
    printf("+++output tree\n");
    for(i=0; i<n; i++)
    {
        printf("%d->",i);
        for(j=0; j<n; j++)
        {
            if(adj[i][j]!=0)
                printf("%d ",j);
        }
        printf("\n");
    }

}
void treetoseq(int **adj,int n,int seq[])
{
    int i,j,deg[n],count, min_deg;

    for(i=0; i<n; i++)
    {
        count=0;
        for(j=0; j<n; j++)
        {
            if(adj[i][j]!=0)
                count++;
        }
        deg[i]=count;
    }
    for(i=0; i<(n-2); i++)
    {
        min_deg=n+1;
        for(j=0; j<n; j++)
        {
            if(deg[j]==1 && j<min_deg)
                min_deg=j;
        }
        for(j=0; j<n; j++)
        {
            if(adj[min_deg][j]!=0)
                seq[i]=j;
        }
        for(j=0; j<n; j++)
        {
            if(adj[min_deg][j]!=0)
            {
                deg[j]-=1;
                deg[min_deg]-=1;
                adj[min_deg][j]=0;
                adj[j][min_deg]=0;
            }
        }
    }

    for(i=0; i<(n-2); i++)
        printf("%d  ",seq[i]);


}
int main()
{
    int n,i,j;
    printf("number of vertices=");
    scanf("%d",&n);
    int **adj,k,seq[n];

    adj=(int **)malloc(n*sizeof(int *));
    for(i=0; i<n; i++)
        adj[i]=(int *)malloc(n*sizeof(int));
    printf("+++reading the adjacency matrix\n");
    for(i=0; i<n; i++)
    {
        for(j=i; j<n; j++)
        {
            scanf("%d",&adj[i][j]);
            adj[j][i]=adj[i][j];
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=i; j<n; j++)
            printf("%d\t",adj[i][j]);
        printf("\n");
        for(k=0; k<=i; k++)
            printf("\t");
    }
    printf("\n");
    treetoseq(adj,n,seq);
    printf("\n");
    for(i=0; i<(n-2); i++)
        printf("%d  ",seq[i]);
    seqtotree(seq,n);
}
