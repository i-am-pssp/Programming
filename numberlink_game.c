#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node
{
    struct node *prt;
    int rank,path,flag;
} node;
node **initboard(int n)
{
    node **B;
    int i,j;
    B = (node **)malloc(n*sizeof(node *));
    for (i=0; i<n; ++i)
        B[i] = (node *)malloc(n * sizeof(node));
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            B[i][j].rank=0;

            B[i][j].prt=NULL;
            B[i][j].path=0;
            B[i][j].flag=0;
        }
    }
    return B;
}
node *findset(node *p)
{
    while(p->prt!=NULL)
        p=p->prt;
    return p;
}
void  setunion(node *p,node *q)
{
    node *root1,*root2;
    root1=findset(p);
    root2=findset(q);
    if(root1->rank<root2->rank)
    {
        root1->prt=root2;
    }
    else
    {
        root2->prt=root1;
        if(root1->rank==root2->rank)
            root1->rank++;
    }
}
int addpath(node **B,int n)
{
    int i,j,k,l,temp1,temp2,z=1,ch=0,count=0,arb=0,result;
    temp1=rand()%(n*n);
    while(1)
    {
        i=temp1/n;
        j=temp1%n;
        printf("%d,%d\n",i,j);
        if(findset(&B[i][j])->rank==0)
        {

            while(1)
            {
                temp2=rand()%4;
                printf("%d\n",temp2);
                while(z<=4)
                {
                    switch(temp2)
                    {
                    case 0 :
                    {
                        if(i>=1)
                        {
                            k=i-1;
                            l=j;
                            if(j<=n-2)
                            {
                                if(findset(&B[i][j])==findset(&B[i-1][j+1]))
                                    count++;
                            }
                            if(j>=1)
                            {
                                if(findset(&B[i][j])==findset(&B[i-1][j-1]))
                                    count++;
                            }
                            if(i>=2)
                            {
                                if(findset(&B[i][j])==findset(&B[i-2][j]))
                                    count++;
                            }
                            if(count!=0)
                            {
                                B[i][j].flag=1;
                                result=1;
                                printf("(%d,%d) ",B[i][j]);
                                return result;
                            }
                            if(findset(&B[k][l])->rank!=0)
                            {
                                temp2=1;
                                z++;
                                continue;
                            }
                            else
                            {
                                if(arb==0)
                                {
                                    B[i][j].flag=1;
                                    printf("flag of (%d,%d) is %d\n",i,j,B[i][j].flag);
                                    arb++;
                                }
                                printf("(%d,%d) ",i,j);
                                setunion(&B[i][j],&B[k][l]);
                            }
                        }
                        else
                        {
                            temp2=1;
                            z++;
                            continue;
                        }
                        break;
                    }
                    case 1:
                    {
                        if(j<=n-2)
                        {
                            k=i;
                            l=j+1;
                            if(j<=n-3)
                            {
                                if(findset(&B[i][j])==findset(&B[i][j+2]))
                                    count++;
                            }
                            if(i>=1)
                            {
                                if(findset(&B[i][j])==findset(&B[i-1][j+1]))
                                    count++;
                            }
                            if(i<=n-2)
                            {
                                if(findset(&B[i][j])==findset(&B[i+1][j+1]))
                                {
                                    printf("count is %d\n",count);
                                    count++;
                                    printf("count is %d\n",count);
                                }
                            }
                            if(count!=0)
                            {
                                B[i][j].flag=1;
                                result=1;
                                printf("(%d,%d) ",B[i][j]);
                                return result;
                            }
                            if(findset(&B[k][l])->rank!=0)
                            {

                                temp2=2;
                                z++;
                                continue;
                            }
                            else
                            {
                                if(arb==0)
                                {
                                    B[i][j].flag=1;
                                    printf("flag of (%d,%d) is %d\n",i,j,B[i][j].flag);
                                    arb++;
                                }
                                printf("(%d,%d) ",i,j);
                                setunion(&B[i][j],&B[k][l]);
                            }
                        }
                        else
                        {
                            temp2=2;
                            z++;
                            continue;
                        }
                        break;
                    }
                    case 2 :
                    {
                        if(j>=1)
                        {
                            k=i;
                            l=j-1;
                            if(j>=2)
                            {
                                if(findset(&B[i][j])==findset(&B[i][j-2]))
                                    count++;
                            }
                            if(i>=1)
                            {
                                if(findset(&B[i][j])==findset(&B[i-1][j-1]))
                                    count++;
                            }
                            if(i<=n-2)
                            {
                                if(findset(&B[i][j])==findset(&B[i+1][j-1]))
                                    count++;
                            }
                            if(count!=0)
                            {
                                B[i][j].flag=1;
                                result=1;
                                printf("(%d,%d) ",i,j);

                                return result;
                            }
                            if(findset(&B[k][l])->rank!=0)
                            {

                                temp2=3;
                                z++;
                                continue;
                            }
                            else
                            {
                                if(arb==0)
                                {
                                    B[i][j].flag=1;
                                    printf("flag of (%d,%d) is %d\n",i,j,B[i][j].flag);
                                    arb++;
                                }
                                printf("(%d,%d) ",B[i][j]);
                                setunion(&B[i][j],&B[k][l]);
                            }
                        }
                        else
                        {
                            temp2=3;
                            z++;
                            continue;
                        }
                        break;
                    }
                    case 3:
                    {
                        if(i<=n-2)
                        {
                            k=i+1;
                            l=j;
                            if(j<=n-2)
                            {
                                if(findset(&B[i][j])==findset(&B[i+1][j+1]))
                                    count++;
                            }
                            if(j>=1)
                            {
                                if(findset(&B[i][j])==findset(&B[i+1][j-1]))
                                    count++;
                            }
                            if(i<=n-3)
                            {
                                if(findset(&B[i][j])==findset(&B[i+2][j]))
                                    count++;
                            }
                            if(count!=0)
                            {
                                B[i][j].flag=1;
                                result=1;
                                printf("(%d,%d) ",B[i][j]);
                                return result;
                            }
                            if(findset(&B[k][l])->rank!=0)
                            {

                                temp2=0;
                                z++;
                                continue;
                            }
                            else
                            {
                                if(arb==0)
                                {
                                    B[i][j].flag=1;
                                    printf("flag of (%d,%d) is %d\n",i,j,B[i][j].flag);
                                    arb++;
                                }
                                printf("(%d,%d) ",i,j);
                                setunion(&B[i][j],&B[k][l]);
                            }
                        }
                        else
                        {
                            temp2=0;
                            z++;
                            continue;
                        }
                        break;
                    }

                    }
                    break;

                }
                if(z==5)
                {
                    result=0;
                    printf("%d\n",result);
                    return result;

                }
                printf("Loop ends\n");
                i=k;
                j=l;
                z=1;
            }
        }
        else
        {
            if(temp1<(n*n-1))
            {
                temp1++;
                continue;
            }
            else
            {
                temp1=0;
                continue;
            }
        }
    }
}
void addpathnum(node **B,int n)
{
    int i,j,k=1;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(findset(&(B[i][j]))->rank==0)
                B[i][j].path=0;
            else
            {
                if(findset(&(B[i][j]))->path==0)
                {
                    findset(&(B[i][j]))->path=k;
                    B[i][j].path=k;
                    k++;
                }
                else
                    B[i][j].path=findset(&(B[i][j]))->path;
            }
        }

    }
}
void printboard(node **B,int n)
{
    printf("++the puzzle\n");
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(B[i][j].path==0)
                printf("*  ");
            else
            {
                if(B[i][j].flag==0)
                    printf("   ");
                else
                    printf("%d  ",B[i][j].path);
            }
        }
        printf("\n");
    }
    printf("+++the solution\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(B[i][j].path==0)
                printf("*  ");
            else
                printf("%d  ",B[i][j].path);
        }
        printf("\n");
    }
}
int main()
{
    int n,result=1;
    srand((unsigned int)time(NULL));
    printf("enter n\n");
    scanf("%d",&n);
    node **B;
    printf("+++initializing board..\n");
    B=initboard(n);
    printf("+++Attempting to add new paths\n");
    while(result==1)
    {
        result=addpath(B,n);
        printf("\n");
    }
    printf("+++Assigning path numbers\n");
    addpathnum(B,n);
    printboard(B,n);
}
