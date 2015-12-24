#include<stdio.h>
#include<stdlib.h>
void printsol(int **s,int i,int j)
{
    if(i==j)
        printf("A[%d] ",i);
    else
    {
        printf("(");
        printsol(s,i,s[i][j]);
        printsol(s,s[i][j]+1,j);
        printf(")");
    }
}
void function(int *p,int n)
{
    int i,j,**s,k,l;
    long long int **m,q;
    m=(long long  int **)malloc((n+1)*sizeof(long long  int*));
    for(i=1; i<=5; i++)
        m[i]=(long long  int *)malloc((n+1)*sizeof(long long  int));
    s=(int **)malloc((n+1)*sizeof( int*));
    for(i=1; i<=5; i++)
        s[i]=(int *)malloc((n+1)*sizeof(int));
    for(i=1; i<=5; i++)
    {
        m[i][i]=0;
        s[i][i]=-1;
    }
    for(l=2; l<=5; l++)
    {
        for(i=1; i<=(5-l+1); i++)
        {
            j=i+l-1;
            m[i][j]=10000000;
            for(k=i; k<j; k++)
            {
                q=m[i][k]+m[k+1][j]+(long)(p[i-1]*p[k]*p[j]);
                if(q<=m[i][j])
                {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }

        }
    }
    printf("number of calcs=%d",m[1][5]);
   printsol(s,1,n);
}
int main()
{
    int n=5,i;

    int *p;
    p=(int *)malloc((n+1)*sizeof(int ));
    printf("enter dimensions \n");
    for(i=0; i<=n; i++)
        scanf("%d",&p[i]);
    function(p,n);
}

