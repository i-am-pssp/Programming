#define C 100
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int startA,startB,endA,endB;
} node;
void packpos(int ref[],int m)
{
    int i=0,j=0,sum,count=0;
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
        (count)++;
    }
   printf("total cartons needed=%d\n",(count));
}
int  packpos_dup1(int ref[],int m,int i,int count)
{
    int sum,j=0;
    while(i<m)
    {
        sum=0;
     while(sum+ref[j]<=C && j<m)
        {
           sum+=ref[j];
            j++;
            i++;
        }
       count++;
    }
    return count;
}
void  packpos_dup2(int ref[],int m,int i,int num)
{
    int sum,j=0;
    while(i<m)
    {
        sum=0;
        printf("carton %d : packing B[",num);
        while(sum+ref[j]<=C && j<m)
        {
            printf("%d ",j);
            sum+=ref[j];
            j++;
            i++;
        }
        printf("]\n");
        /*printf(" : Total cost =%d\n",sum);*/
        num++;
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

}
void packtwo(int A[],int B[],int m,int n)
{

    int i,j,a,b,k,l,t[100][100],x,min,sum;
    node s[100][100];
    t[m][n]=0;
    t[m][n-1]=t[m-1][n]=1;
    if(A[m-1]+B[n-1]<=C)
        t[m-1][n-1]=1;
    else
        t[m-1][n-1]=2;
    for(i=n-1; i>=0; i--)
    {

        t[m][i]=packpos_dup1(B,n,i,0);
    }
    for(i=m-1; i>=0; i--)
    {

        t[i][n]=packpos_dup1(A,m,i,0);
    }
    for(i=m-1; i>=0; i--)
    {
        for(j=n-1; j>=0; j--)
        {
            sum=0;
            t[i][j]=1000;
            for(a=i; a<m; a++)
            {
                sum+=A[a];
                if(sum<=C)
                {
                    for(b=j; b<n; b++)
                    {
                        if(sum+B[b]<=C && b<n)
                        {
                            x=1+t[a+1][b+1];
                            if(x<=t[i][j])
                            {
                                t[i][j]=x;
                                s[i][j].startA=i;
                                s[i][j].startB=j;
                                s[i][j].endA=a;
                                s[i][j].endB=b;

                            }
                        }
                        else
                        {

                            x=1+t[a+1][b];
                            if(x<=t[i][j])
                            {
                                t[i][j]=x;

                                s[i][j].startA=i;
                                s[i][j].endA=a;
                                if(b==j)
                                {
                                    s[i][j].startB=-1;
                                    s[i][j].endB=-1;
                                }
                                else
                                {
                                    s[i][j].startB=j;
                                    s[i][j].endB=b-1;
                                }

                            }
                        }
                        break;
                    }
                }

                else
                {
                    x=1+t[a][j];
                    if(x<=t[i][j])
                    {
                        t[i][j]=x;
                        s[i][j].startA=i;
                        s[i][j].endA=a-1;
                        s[i][j].startB=-1;
                        s[i][j].endB=-1;

                    }
                    break;
                }
            }
        }
    }
    /*for(i=m-1; i>=0; i--)
    {
        for(j=n-1; j>=0; j--)
        {
            printf("t[%d][%d]=%d\n",i,j,t[i][j]);
            printf("s[%d][%d].startA=%d\n",i,j,s[i][j].startA);
            printf("s[%d][%d].endA=%d\n",i,j,s[i][j].endA);
            printf("s[%d][%d].startB=%d\n",i,j,s[i][j].startB);
            printf("s[%d][%d].endB=%d\n",i,j,s[i][j].endB);
        }
    }*/
    printf("total cartons needed:%d\n",t[0][0]);
          k=0, l=0;
    for(i=1;i<=t[0][0];i++)
    {
       if(k<m)
        {
        printf("carton %d : packing ",i);
        printf("A[ %d..%d ] ",s[k][l].startA,s[k][l].endA);
        if(s[k][l].startB!=-1)
            {
                printf(" B[%d ..%d]\n",s[k][l].startB,s[k][l].endB);
                l=s[k][l].endB+1;
            }
            else
            {
                printf("\n");
            }
            k=s[k][l].endA+1;
        }
        else
        {
           j=0,l=0;
            while(j<m)
            {
                if(s[j][l].endB!=-1)
                    l=s[j][l].endB+1;
                j=s[j][l].endA+1;
            }
            packpos_dup2(B,n,l,i);
            break;
        }
    }

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

