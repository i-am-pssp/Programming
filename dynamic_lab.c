#define C 100
#include<stdio.h>
#include<stdlib.h>
void packpos(int ref[],int m)
{
    int i=0,j=0,sum,count=1;
    while(i<m)
    {
        sum=0;
        printf("carton %d : packing A[",count);
        while(sum+ref[j]<=C && j<m)
        {
            printf("%d ",j);
            sum+=ref[j];
            j++;
            i++;
        }
        printf("]: Total cost =%d\n",sum);
        count++;
    }
    printf("total cartons needed=%d\n",count-1);
}
void printsol(int t[],int s[],int i,int j)
{
    if(i==j)
    {
        printf("broken at %d \n",i);
    }
    else
    {
        printsol(t,s,s[i],j);
    }
}
void packposneg(int A[],int m)
{
    int i,j,l,k,t[100],s[100],sum,p,count=1;
    for(i=0; i<m; i++)
        t[i]=1000;
    t[m-1]=1;
    t[m]=0;
    for(i=m-2; i>=0; i--)
    {
        sum=A[i];
        for(k=i+1; k<=m-1; k++)
        {
            sum+=A[k];
            if(sum<=C)
            {
                p=1+t[k+1];
                if(p<t[i])
                {
                    t[i]=p;
                    s[i]=k;
                }
            }
        }
    }
    printf("total cartons needed=%d\n",t[0]);
    /* printsol(t,s,0,m-1);*/
    printf("carton %d :packing A[%d..%d]\n",count,0,s[0]);
    count++;
    printf("carton %d :packing A[%d..%d]\n",count,s[0]+1,m-1);
}
int function(int A[],int B[],int P[],int Q[],int t[][100],int i,int j,int m,int n,int *flag)
{
    int sum,k,count=1;
    if(i==m-1 && j==n-1)
    {
        if(P[i+1]+Q[j+1]<=C)
            return 1;
        else
            return 2;
    }
    if(i>m-1)
    {
        k=j;
        while(j<n)
        {
            sum=0;
            printf("carton  : B[");
            while(sum+B[j]<=C && j<n)
            {
                printf("%d ",j);
                sum+=B[j];
                j++;
                k++;
            }
            count++;

            printf("]");
            /* printf("]: Total cost =%d\n",sum);
             count++;*/
        }
        *flag=-1;
        return (count-1);
    }
    if(j>n-1)
    {
        k=i;
        while(i<m)
        {
            sum=0;
            printf("carton  : packing A[");
            while(sum+A[i]<=C && i<m)
            {
                printf("%d ",i);
                sum+=A[i];
                i++;
                k++;
            }
            count++;

            printf("]");
            /* printf("]: Total cost =%d\n",sum);
             count++;*/
        }
        *flag=-1;
        return (count-1);
    }
    int k1,k2,min=0;

    for(k1=i; k1<m; k1++)
    {
        if(P[k1+1]-P[i]<=C)
        {
            for(k2=j; k2<n; k2++)
            {
                if(P[k1+1]-P[i]+Q[k2+1]-Q[j]<=C)
                {
                    printf("carton : A[%d]B[%d]\n",k1,k2);
                    if(t[i][j]==0)
                        t[i][j]=1+function(A,B,P,Q,t,k1+1,k2+1,m,n,flag);
                    if(min==0)
                    min=t[i][j];
                    if(t[i][j]<=min)
                        min=t[i][j];
                    if(*flag==-1)
                    {
                        return min;
                    }
                }
                else
                    break;

            }

            if(k2==j)
            {
                printf("carton : A[%d]\n",k1);
                if(t[i][j]==0)
                        t[i][j]=1+function(A,B,P,Q,t,k1+1,k2+1,m,n,flag);
                    if(min==0)
                    min=t[i][j];
                    if(t[i][j]<=min)
                        min=t[i][j];
                if(*flag==-1)
                {
                    return t[i][j];
                }

            }
        }
        else
            break;
    }
}
void packtwo(int A[],int B[],int m,int n)
{
    printf("*1\n");
    int i,j,k1,k2,l,t[100][100],s[100][100],P[100],Q[100],sum1,sum2,x,flag=0;
    t[m][n-1]=1;
	t[m-1][n]=1;
	t[m][n]=0;
	sum=0;
    for(i=m-2;i>=0;i--)
	{
		k=i+1;
		sum=0;
		while(k<=m&&((sum+a[k])<=C))
		{
			sum=sum+a[k];
			k++;
		}
		if(sum+a[k]>C&&k<=m)
		{
			s[i][n]=1+s[k-1][n];
			t[i][n].A=k;
			t[i][n].B=n+1;
		}
		else
		{
			s[i][n]=1;
			t[i][n].A=m+1;
			t[i][n].B=n+1;
		}
	}
   /* for(i=1,P[0]=0; i<=m; i++)
    {
        P[i]=P[i-1]+A[i-1];
    }
    for(i=1,Q[0]=0; i<=n; i++)
    {
        Q[i]=Q[i-1]+B[i-1];
    }
    for(i=0; i<=m; i++)
        printf("%d  ",P[i]);
    printf("\n");
    for(i=0; i<=n; i++)
        printf("%d  ",Q[i]);
    printf("total cartons needed:%d\n",function(A,B,P,Q,t,0,0,m,n,&flag));*/
}

int main()
{
    int m,n,i,A[100],A2[100],B[100],ref[100];

    printf("enter m\n");
    scanf("%d",&m);
    printf("enter m positive integers\n");
    for(i=0; i<m; i++)
    {
        scanf("%d",&A[i]);
    }
    for(i=0; i<m; i++)
        ref[i]=A[i];
    packpos(ref,m);
    /* printf("enter elements for 2nd array\n");
     for(i=0; i<m; i++)
         scanf("%d",&A2[i]);

     packposneg(A2,m);*/
    printf("enter n\n");
    scanf("%d",&n);
    printf("enter n positive integers\n");
    for(i=0; i<n; i++)
    {
        scanf("%d",&B[i]);
    }
    packtwo(A,B,m,n);
}

