#include<stdio.h>
void permutate(int A[],int m,int n)
{
   int i,j,temp;
    if( m==n)
    {
        for(i=1;i<=n;i++)
            printf("%d ",A[i]);
        printf("\n");
    }
    for(i=m;i<=n;i++)
    {
        temp=A[m];
        A[m]=A[i];
        A[i]=temp;
        permutate(A,m+1,n);
        temp=A[m];
        A[m]=A[i];
        A[i]=temp;
    }
}
int main()
{
    int n,i,temp;
    printf("enter n value\n");
    scanf("%d",&n);
    int A[n];
    printf("enter n numbers \n");
    for(i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
    }
    for(i=1;i<=n;i++)
    {
        temp=A[1];
        A[1]=A[i];
        A[i]=temp;
        permutate(A,2,n);
        temp=A[1];
        A[1]=A[i];
        A[i]=temp;
    }
}

