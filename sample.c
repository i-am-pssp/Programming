#include<stdio.h>
#include<stdlib.h>
void function(int *p,int n)
{
    int c[n+1],b[n+1],i;
    c[0]=0;c[1]=1;b[1]=p[1];
    for(i=2;i<=n;i++)
    {
        if(p[i]>=p[i-1])
        {
            if(p[i]>=b[i-1])
               {
                b[i]=p[i];
                c[i]=1+c[i-1];
                }
            else
            {
                b[i]=b[i-1];
            c[i]=c[i-1];
            }
            printf("b[%d]=%d  ",i,b[i]);
        }
        else
        {
            c[i]=c[i-1];

                b[i]=b[i-1];
                printf("b[%d]=%d  ",i,b[i]);
        }
    }
printf("length of the longest sequence is %d\n",c[n]);
   i=1;
   printf("%d  ",b[i++]);
   while(i<=n)
   {
    if(b[i]!=b[i-1])
   {
       printf("%d  ",b[i]);
       i++;
   }
   else
   {
       while(i<=n && b[i]==b[i-1])
        i++;
   }
   }
}
int main()
{
    int n,i,*p;
    p=(int *)malloc((n+1)*sizeof(int));
    printf("n=");
    scanf("%d",&n);
    printf("enter %d numbers\n",n);
    for(i=1;i<=n;i++)
        scanf("%d",&p[i]);
    function(p,n);
}
