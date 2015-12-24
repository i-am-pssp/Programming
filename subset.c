#include<stdio.h>
#include<math.h>
int fun(int i,int j,int n)
{
    int b[n],x;
for(x=n-1;x>=0;x--)
{
    b[x]=i%2;
    i=i/2;
}
return b[j];
}
void subset(int *a,int n)
{
   int i,j;
   for(i=0;i<pow(2,n);i++)
   {
       for(j=0;j<n;j++)
       {
           if(fun(i,j,n))
            printf("%d ",a[j]);
       }
       printf("\n");
   }
}
int main()
{
    int i,j,n,*a;
    printf("n=");
    scanf("%d",&n);
    a=(int *)malloc((n+1)*sizeof(int));
    printf("elements:\n");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("set is ");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    subset(a,n);
}
