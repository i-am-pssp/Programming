#include<stdio.h>
#include<stdlib.h>
void fastestway(int e[],int x[],int **a,int **t,int n)
{
    int f[3][n+1],l[3][n+1],F,L,i,j;
   f[1][1]=e[1]+a[1][1];
    f[2][1]=e[2]+a[2][1];
    for(j=2; j<=n; j++)
    {
        if(f[1][j-1]+a[1][j]<=f[2][j-1]+t[2][j-1]+a[1][j])
        {
            f[1][j]=f[1][j-1]+a[1][j];
            l[1][j]=1;

        }
        else
        {
            f[1][j]=f[2][j-1]+t[2][j-1]+a[1][j];
            l[1][j]=2;
        }
        if(f[2][j-1]+a[2][j]<=f[1][j-1]+t[1][j-1]+a[2][j])
        {
            f[2][j]=f[2][j-1]+a[2][j];
            l[2][j]=2;

        }
        else
        {
            f[2][j]=f[1][j-1]+t[1][j-1]+a[2][j];
            l[2][j]=1;

        }
    }
    if(f[1][n]+x[1]<=f[2][n]+x[2])
    {
        L=1;
        F=f[1][n]+x[1];
    }
    else
    {
        L=2;
        F=f[2][n]+x[2];
    }

    i=L;
    printf("line %d...station %d\n",i,n);
    for(j=n;j>=2;j--)
    {
        i=l[i][j];
    printf("line %d...station %d\n",i,j-1);
    }
}
int main()
{
    int n,e[3],x[3],i;
    printf("n=");
    scanf("%d",&n);
    int **a,**t;
    a=(int **)malloc(n*sizeof(int *));
    t=(int **)malloc(n*sizeof(int *));
    for(i=1;i<=n;i++)
        a[i]=(int *)malloc((n+1)*sizeof(int ));
     for(i=1;i<=n;i++)
        t[i]=(int *)malloc((n+1)*sizeof(int ));
    printf("enter e1 e2 x1 x2\n");
    scanf("%d%d%d%d",&e[1],&e[2],&x[1],&x[2]);
    printf("for line 1 enter assembly times\n");
    for(i=1; i<=n; i++)
        scanf("%d",&a[1][i]);
    printf("for line 2 enter assembly times\n");
    for(i=1; i<=n; i++)
        scanf("%d",&a[2][i]);
    printf("for line 1 enter transfer times\n");
    for(i=1; i<n; i++)
        scanf("%d",&t[1][i]);
    printf("for line 2 enter transfer times\n");
    for(i=1; i<n; i++)
        scanf("%d",&t[2][i]);
    fastestway(e,x,a,t,n);

}

