#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//function packpos for part 1 as given in the question. return type void. runs in O(m) time
void packpos(int *p,int m)
{
    int sum=0,j=1,i;
    printf("Carton %d : A[ ",j);
    for(i=0; i<m;)
    {
        if(sum+p[i]>100)
        {
            printf(" ]\t total cost = %d\n",sum);
            sum=0;
            j++;
            printf("Carton %d : A[ ",j);
        }
        else
        {
            printf("%d ",i);
            sum+=p[i];
            i++;
        }
    }
    printf(" ]\t total cost = %d\n",sum);
    printf("+++Total number of cartons needed = %d\n",j);

}
typedef struct node
{
    int start;
    int end;
} index;
void packposneg(int *p,int m)
{
    int sum,i,j,q=m,*t;
    index *s;
    t=(int*)malloc((m+1)*sizeof(int));
    s=(index*)malloc((m+1)*sizeof(index));
    t[1]=1;
    t[0]=0;
    s[0].start=0;
    s[0].end=0;
    for(i=1; i<=m-1; i++)
    {
        for(j=i,q=i+1,sum=0; j>=0; j--)
        {
            sum+=p[j];
            if(sum<=100)
            {
                if(1+t[j]<q)
                {
                    q=1+t[j];
                    s[i].start=j;
                    s[i].end=i;
                }
            }
        }
        t[i+1]=q;
    }
    int cost,x;
    for(i=m-1,j=t[m]; i>=0; )
    {
        cost=0;
        for(x=s[i].start; x<=s[i].end; x++) cost+=p[x];
        printf("\n Carton %d : A[%d..%d]  cost=%d\n",j,s[i].start,s[i].end,cost);
        i=s[i].start-1;
        j--;


    }
    printf("+++The number of cartons required are %d\n",t[m]);
}
/*
Structure defined to hold the start and end of both the arrays at every t[i][j] in the optimal solution
*/
typedef struct node1
{
    int startp;
    int endp;
    int startq;
    int endq;
} index2;
/*
Function packtwo to formulate the optimal solution using DP.
reccurance relation : t[i][j]=min(i<=k1<m,j<=k2<n 1+t[k1+1][k2+1])
where k1 and k2 are the indexes upto where the sum<=100 is considered
*/
void packtwo(int *p,int *q,int m,int n)
{
    int **t,i,j,k,sum,sum1,sum2,q1,q2,var1,var2,var3,var4,initsum,initsum1;
    index2 **s;
    s=(index2**)malloc((m+1)*sizeof(index2*));
    for(i=0; i<=m; i++) s[i]=(index2*)malloc((n+1)*sizeof(index2));
    t=(int**)malloc((m+1)*sizeof(int*));
    for(i=0; i<=m; i++) t[i]=(int*)malloc((n+1)*sizeof(int));       //the two for loops basically does the functions
    int k1,k2,min;                                                  //of packposneg function individually for the two arrays
    t[m][n]=0;
    s[m][n].startp=m;
    s[m][n].endp=m;
    s[m][n].startq=n;
    s[m][n].endq=n;
    t[m-1][n]=1;
    s[m-1][n].startp=m-1;
    s[m-1][n].endp=m-1;
    s[m-1][n].startq=-1;
    s[m-1][n].endq=-1;

    t[m][n-1]=1;
    s[m][n-1].startp=-1;
    s[m][n-1].endp=-1;
    s[m][n-1].startq=n-1;
    s[m][n-1].endq=n-1;
    j=n-1;


    for(i=m-2,sum=p[m-1]; i>=0; i--)
    {
        if(sum+p[i]<=100)
        {
            t[i][n]=t[i+1][n];
            sum+=p[i];
            s[i][n].startp=i;
            s[i][n].endp=s[i+1][n].endp;
            s[i][n].startq=-1;
            s[i][n].endq=-1;
        }
        else
        {
            t[i][n]=1+t[i+1][n];
            sum=p[i];
            s[i][n].startp=i;
            s[i][n].endp=i;
            s[i][n].startq=-1;
            s[i][n].endq=-1;

        }
    }
    for(i=n-2,sum=q[n-1]; i>=0; i--)
    {
        if(sum+q[i]<=100)
        {
            t[m][i]=t[m][i+1];
            sum+=q[i];
            s[m][i].startp=-1;
            s[m][i].endp=-1;
            s[m][i].startq=i;
            s[m][i].endq=s[m][i+1].endq;
        }
        else
        {
            t[m][i]=1+t[m][i+1];
            sum=q[i];
            s[m][i].startp=-1;
            s[m][i].endp=-1;
            s[m][i].startq=i;
            s[m][i].endq=i;
        }
    }


    for(j=n-1; j>=0; j--)                                            //O(c*c*m*n)=O(m*n) as c is a constant
    {
        for(i=m-1; i>=0; i--)
        {
            for(k1=i,sum=0,min=m+n; k1<m; k1++)                       //loop runs max for c times as all are positive values
            {
                if(sum+p[k1]<=100)
                {
                    sum+=p[k1];
                    initsum=sum;

                    for(k2=j; k2<n; k2++)                                 //again this loop also runs for max of c times
                    {
                        if(sum+q[k2]<=100)
                        {
                            sum+=q[k2];
                            continue;
                        }
                        else
                        {
                            if(1+t[k1+1][k2]<min)
                            {
                                min=1+t[k1+1][k2];        //checks if the obtained soln is less than previous and if so replaces
                                s[i][j].startp=i;
                                s[i][j].endp=k1;
                                if(k2!=j)
                                {
                                    s[i][j].startq=j;
                                    s[i][j].endq=k2-1;
                                }
                                else
                                {
                                    s[i][j].startq=-1;
                                    s[i][j].endq=-1;
                                }
                            }
                            break;
                        }
                    }
                    if(k2==n)
                    {
                        if(1+t[k1+1][k2]<min)
                        {
                            min=1+t[k1+1][k2];        //checks if the obtained soln is less than previous and if so replaces
                            s[i][j].startp=i;
                            s[i][j].endp=k1;
                            s[i][j].startq=j;
                            s[i][j].endq=k2-1;
                        }

                    }
                    sum=initsum;
                }
                else
                {
                    if(1+t[k1][j]<min)
                    {
                        min=1+t[k1][j];                 //checks if the obtained soln is less than previous and if so replaces
                        s[i][j].startp=i;
                        s[i][j].endp=k1-1;
                        s[i][j].startq=-1;
                        s[i][j].endq=-1;
                    }
                    break;
                }
            }
            t[i][j]=min;                                             //optimal soln is obtained and assigned to t[i][j]
        }
    }


    printf("\n\n+++Total number of Cartons = %d\n",t[0][0]);


    i=0;
    j=0,k=1;
    int i1,j1,cost,x;
    for(;;)                                                        //function to print the obtained sequence
    {
        cost=0;
        printf("Carton %d : A[%d..%d] ",k,s[i][j].startp,s[i][j].endp);
        k++;
        for(x=s[i][j].startp; x<=s[i][j].endp; x++) cost+=p[x];
        if(s[i][j].startq!=-1)
        {
            for(x=s[i][j].startq; x<=s[i][j].endq; x++) cost+=q[x];
            printf("B[%d..%d] cost=%d\n",s[i][j].startq,s[i][j].endq,cost);

        }
        else printf(" cost=%d\n",cost);
        i1=s[i][j].endp+1;
        if(s[i][j].startq!=-1) j1=s[i][j].endq+1;
        else j1=j;
        if(s[i][j].endp==m-1)
        {
            i=i1;
            j=j1;
            break;
        }
        i=i1;
        j=j1;
    }
    if(k!=t[0][0]+1)
    {
        if(i>m)i=m;
        for(x=j;;)
        {
            cost=0;
            for(x=s[i][j].startq; x<=s[i][j].endq; x++) cost+=q[x];
            printf("Carton %d : B[%d..%d] cost=%d\n",k,s[i][j].startq,s[i][j].endq,cost);
            if(s[i][j].endq==n-1) break;
            j=s[i][j].endq+1;

        }
    }
}

int main()
{
    int *p,m,i,*a,n,*q,*p1;
    printf("m=");
    scanf("%d",&m);
    p=(int*)malloc(m*sizeof(int));
    p1=(int*)malloc(m*sizeof(int));
    printf("+++Input array with positive entries : \n");
    for(i=0; i<m; i++)
    {
        scanf("%d",&p[i]);
    }
    packpos(p,m);
   /* printf("+++Input entries with positive and negative numbers : \n");
    for(i=0; i<m; i++)
    {
        scanf("%d",&p1[i]);
    }
    packposneg(p1,m);*/
    printf("n=");
    scanf("%d",&n);
    q=(int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++) scanf("%d",&q[i]);
    packtwo(p,q,m,n);
    return 0;
}
