#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node/*defining node*/
{
    struct node *prt;
    int rank,path,flag;
} node;
node **initboard(int n) /*initializing the board*/
{
    node **B;
    int i,j;
    B = (node **)malloc(n*sizeof(node *));
    for (i=0; i<n; ++i)
        B[i] = (node *)malloc(n * sizeof(node));
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++) /*initializing all to 0*/
        {
            B[i][j].rank=0;
            B[i][j].prt=NULL;
            B[i][j].path=0;
            B[i][j].flag=0;
        }
    }
    return B;
}
node *findset(node *p) /*finding the root of the tree*/
{
    while(p->prt!=NULL)
        p=p->prt;
    return p;
}
void  setunion(node *p,node *q) /*merging 2 trees*/
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
    int i,j,k,l,temp1,temp2,z=1,ch=0,count=0,result,arb,check=0,t=0;
    temp1=rand()%(n*n);
    while(1)  /*locating 2 neighbour squares*/
    {

        i=temp1/n;
        j=temp1%n;
        z=1;
        /*printf("i is %d, j is %d\n",i,j);*/

        if(findset(&B[i][j])->rank==0)
        {
            temp2=rand()%4;
            /* printf("%d\n",temp2);*/
            while(z<=4)
            {
                switch(temp2)  /*searching for neighbour*/
                {
                case 0 :
                {
                    count=0;
                    if(i>=1)
                    {
                        k=i-1;
                        l=j;

                        if(findset(&B[k][l])->rank!=0)
                        {
                            temp2=1;
                            z++;
                            continue;
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
                    count=0;
                    if(j<=n-2)
                    {
                        k=i;

                        l=j+1;

                        if(findset(&B[k][l])->rank!=0)
                        {

                            temp2=2;
                            z++;
                            continue;
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
                    count=0;
                    if(j>=1)
                    {
                        k=i;
                        l=j-1;

                        if(findset(&B[k][l])->rank!=0)
                        {

                            temp2=3;
                            z++;
                            continue;
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
                    count=0;
                    if(i<=n-2)
                    {
                        k=i+1;
                        l=j;

                        if(findset(&B[k][l])->rank!=0)
                        {

                            temp2=0;
                            z++;
                            continue;
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

            if(z==5)  /*if no neighbour found move to next square*/
            {
                /*printf("t=%d\n");*/
                t++;
                temp1++;
                temp1=temp1%(n*n);
                continue;
            }

        }
        else  /*if rank is not 0 go to next square*/
        {
            if(t==n*n)
            {
                return 0;
            }

            else
            {
                /* printf("t=%d\n");*/
                t++;
                temp1++;
                temp1=temp1%(n*n);
                continue;
            }

        }
        break;
    }
    B[i][j].flag=1;  /*an endpoint of a new path*/
    printf("(%d,%d) ",i,j);
    setunion(&B[i][j],&B[k][l]);
    /* printf("new path : (%d,%d)",i,j);*/

    while(1)
    {
        i=k;
        j=l;
        z=1;
        temp2=rand()%4;
        /* printf("%d\n",temp2);*/
        while(z<=4)
        {
            switch(temp2)  /*searching for a proper neighbour*/
            {
            case 0 :
            {

                count=0;
                if(i>=1)
                {

                    k=i-1;
                    l=j;
                    if(findset(&B[k][l])->rank!=0)
                    {
                        temp2=1;
                        z++;
                        continue;
                    }
                    if(j<=n-2) /*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i-1][j+1]))
                            count++;
                    }

                    if(j>=1)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i-1][j-1]))
                            count++;
                    }

                    if(i>=2)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i-2][j]))
                            count++;
                    }

                    if(count!=0) /*proper neighbour not found go to next direction*/
                    {
                        temp2=1;
                        z++;
                        continue;

                        /* B[i][j].flag=1;
                         result=1;
                         printf("(%d,%d) ",i,j);
                         return result;*/
                    }
                    printf("(%d,%d) ",i,j);
                    setunion(&B[i][j],&B[k][l]);

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
                count=0;
                if(j<=n-2)
                {

                    k=i;
                    l=j+1;
                    if(findset(&B[k][l])->rank!=0)
                    {
                        temp2=2;
                        z++;
                        continue;
                    }
                    if(j<=n-3)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i][j+2]))
                            count++;
                    }
                    if(i>=1)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i-1][j+1]))
                            count++;
                    }
                    if(i<=n-2)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i+1][j+1]))
                        {

                            count++;

                        }
                    }
                    if(count!=0) /*proper neighbour not found go to next direction*/
                    {

                        temp2=2;
                        z++;
                        continue;

                        /*B[i][j].flag=1;
                        result=1;
                        printf("(%d,%d) ",i,j);
                        return result;*/
                    }




                    printf("(%d,%d) ",i,j);
                    setunion(&B[i][j],&B[k][l]);

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
                count=0;
                if(j>=1)
                {

                    k=i;
                    l=j-1;
                    if(findset(&B[k][l])->rank!=0)
                    {
                        temp2=3;
                        z++;
                        continue;
                    }
                    /*printf("1");*/
                    if(j>=2)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i][j-2]))
                            count++;
                    }
                    /* printf("2");*/
                    if(i>=1)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i-1][j-1]))
                            count++;
                    }
                    /* printf("3");*/
                    if(i<=n-2)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i+1][j-1]))
                            count++;
                    }
                    /* printf("4");*/
                    if(count!=0) /*proper neighbour not found go to next direction*/
                    {
                        temp2=3;
                        z++;
                        continue;

                        /*B[i][j].flag=1;
                        result=1;
                        printf("(%d,%d) ",i,j);

                        return result;*/
                    }
                    printf("(%d,%d) ",i,j);
                    setunion(&B[i][j],&B[k][l]);

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
                count=0;
                if(i<=n-2)
                {

                    k=i+1;
                    l=j;
                    if(findset(&B[k][l])->rank!=0)
                    {
                        temp2=0;
                        z++;
                        continue;
                    }
                    if(j<=n-2)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i+1][j+1]))
                            count++;
                    }
                    if(j>=1)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i+1][j-1]))
                            count++;
                    }
                    if(i<=n-3)/*checking if the neighbour is proper*/
                    {
                        if(findset(&B[i][j])==findset(&B[i+2][j]))
                            count++;
                    }
                    if(count!=0) /*proper neighbour not found go to next direction*/
                    {

                        temp2=0;
                        z++;
                        continue;

                        /*B[i][j].flag=1;
                        result=1;
                        printf("(%d,%d) ",i,j);
                        return result;*/
                    }
                    printf("(%d,%d) ",i,j);
                    setunion(&B[i][j],&B[k][l]);

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
        /* result=0;
         printf("%d\n",result);
         return result;*/
        if(z==5)
        {
            printf("(%d,%d)",i,j);
            B[i][j].flag=1;
            return 1;
        }
    }
}
void addpathnum(node **B,int n) /*adding path numbers*/
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
void dashes(int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("+-----");
    }
    printf("+\n");
}
void printboard(node **B,int n) /*printing the board*/
{
    printf("++the puzzle\n");
    int i,j;
    for(i=0; i<n; i++)/*printing the puzzle*/
    {
        dashes(n);
        for(j=0; j<n; j++)
        {
            if(B[i][j].path==0)
                printf("|xxxxx");
            else
            {
                if(B[i][j].flag==0)
                    printf("|     ");
                else
                    printf("|  %d  ",B[i][j].path);
            }
        }
        printf("|\n");
    }
    dashes(n);
    printf("+++the solution\n");
    for(i=0; i<n; i++) /*printing the solution*/
    {
        dashes(n);
        for(j=0; j<n; j++)
        {
            if(B[i][j].path==0)
                printf("|xxxxx");
            else
                printf("|  %d  ",B[i][j].path);
        }
        printf("|\n");
    }
    dashes(n);
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
printf("The paths are : ");
    while(1)
    {

        if(addpath(B,n)==1)
        {
printf("\n");
            continue;
        }

        break;
    }
    printf("\n+++Assigning path numbers\n");
    addpathnum(B,n);
    printboard(B,n);
}
