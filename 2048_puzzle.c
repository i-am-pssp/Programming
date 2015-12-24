#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int total;
typedef struct node
{
    int key;
    int flag;
} node;
int  printgame(node ***a,int total)
{
    int i,j,k,count=0;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(a[i][j]->flag==1 && a[i][j]->key==total)
            {
                for(i=0; i<4; i++)
                {
                    for(j=0; j<4; j++)
                    {
                        if(a[i][j]->flag!=0)
                        {
                            printf("|%4d  ",a[i][j]->key);

                        }
                        else
                            printf("|      ");

                    }
                    printf("\n");
                }
                printf("YOU WON!!!\n");
                return 100;
            }
        }
    }
    k=rand()%16;
    while(1)
    {
        i=k/4;
        j=k%4;
        if(a[i][j]->flag==0)
        {

            a[i][j]->key=2;
            a[i][j]->flag=1;
            break;
        }
        else
        {
            if(++k==16)
            {
                k=0;
            }
            count++;
            if(count==16)
            {
                printf("SORRY....GAME OVER!\n");
                return -1;

            }
            continue;

        }
    }
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(a[i][j]->flag!=0)
            {
                printf("|%4d  ",a[i][j]->key);

            }
            else
                printf("|      ");

        }
        printf("\n");
    }

}
int upmove(node ***a)
{
    int i,j,k,temp,y;
    for(j=0; j<4; j++)
    {
        for(i=1; i<=3; i++)
        {
            if(a[i][j]->flag==0)
                continue;
            else
            {
                temp=i-1;
                if(a[i-1][j]->flag==0)
                {
                    while(temp>-1 && a[temp][j]->flag==0  )
                    {
                        temp--;
                    }
                    if(temp==-1)
                        y=temp+1;
                    else
                        y=temp;
                    if(a[y][j]->flag==0)
                    {
                        a[y][j]->flag=1;
                        a[y][j]->key=a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                    else
                    {
                        if(a[y][j]->key==a[i][j]->key)
                        {
                            a[y][j]->key=2*a[i][j]->key;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                        else
                        {
                            a[y+1][j]->key=a[i][j]->key;
                            a[y+1][j]->flag=1;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                    }
                }
                else
                {
                    if(a[i-1][j]->key==a[i][j]->key)
                    {
                        a[i-1][j]->key=2*a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                }
            }
        }
    }
    return printgame(a,total);
}
int leftmove(node ***a)
{
    int i,j,k,temp,y;
    for(i=0; i<4; i++)
    {
        for(j=1; j<=3; j++)
        {
            if(a[i][j]->flag==0)
                continue;
            else
            {
                temp=j-1;
                if(a[i][j-1]->flag==0)
                {
                    while(temp>-1 && a[i][temp]->flag==0  )
                    {
                        temp--;
                    }
                    if(temp==-1)
                        y=temp+1;
                    else
                        y=temp;
                    if(a[i][y]->flag==0)
                    {
                        a[i][y]->flag=1;
                        a[i][y]->key=a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                    else
                    {
                        if(a[i][y]->key==a[i][j]->key)
                        {
                            a[i][y]->key=2*a[i][j]->key;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                        else
                        {
                            a[i][y+1]->key=a[i][j]->key;
                            a[i][y+1]->flag=1;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                    }
                }
                else
                {
                    if(a[i][j-1]->key==a[i][j]->key)
                    {
                        a[i][j-1]->key=2*a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                }
            }
        }
    }
    return printgame(a,total);
}
int downmove(node ***a)
{
    int i,j,k,temp,y;
    for(j=0; j<4; j++)
    {
        for(i=2; i>=0; i--)
        {
            if(a[i][j]->flag==0)
                continue;
            else
            {
                temp=i+1;
                if(a[i+1][j]->flag==0)
                {
                    while(temp<4 && a[temp][j]->flag==0  )
                    {
                        temp++;
                    }
                    if(temp==4)
                        y=temp-1;
                    else
                        y=temp;
                    if(a[y][j]->flag==0)
                    {
                        a[y][j]->flag=1;
                        a[y][j]->key=a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                    else
                    {
                        if(a[y][j]->key==a[i][j]->key)
                        {
                            a[y][j]->key=2*a[i][j]->key;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                        else
                        {
                            a[y-1][j]->key=a[i][j]->key;
                            a[y-1][j]->flag=1;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                    }
                }
                else
                {
                    if(a[i+1][j]->key==a[i][j]->key)
                    {
                        a[i+1][j]->key=2*a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                }
            }
        }
    }
    return printgame(a,total);
}

int rightmove(node ***a)
{
    int i,j,k,temp,y;
    for(i=0; i<4; i++)
    {
        for(j=2; j>=0; j--)
        {
            if(a[i][j]->flag==0)
                continue;
            else
            {
                temp=j+1;
                if(a[i][j+1]->flag==0)
                {
                    while(temp<4 && a[i][temp]->flag==0  )
                    {
                        temp++;
                    }
                    if(temp==4)
                        y=temp-1;
                    else
                        y=temp;
                    if(a[i][y]->flag==0)
                    {
                        a[i][y]->flag=1;
                        a[i][y]->key=a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                    else
                    {
                        if(a[i][y]->key==a[i][j]->key)
                        {
                            a[i][y]->key=2*a[i][j]->key;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                        else
                        {
                            a[i][y-1]->key=a[i][j]->key;
                            a[i][y-1]->flag=1;
                            a[i][j]->key=0;
                            a[i][j]->flag=0;
                        }
                    }
                }
                else
                {
                    if(a[i][j+1]->key==a[i][j]->key)
                    {
                        a[i][j+1]->key=2*a[i][j]->key;
                        a[i][j]->key=0;
                        a[i][j]->flag=0;
                    }
                }
            }
        }
    }
    return printgame(a,total);
}
int main()
{
    srand((unsigned int)time(NULL));
    node ***a;
    printf("             8 -->up \n");
    printf("4 -->left                6 -->right\n");
    printf("             2 -->down\n");
    a=(node***)malloc(4*sizeof(node **));
    int n,i,j,k,ch,res,chance;
    for(i=0; i<4; i++)
        a[i]=(node**)malloc(4*sizeof(node*));
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            a[i][j]=(node*)malloc(sizeof(node));
            a[i][j]->flag=0;
            a[i][j]->key=0;
        }
    }
    printf("You wanna play upto\n");
    printf("16  32  64  128  256  512  1024  2048 4096?\n");
    scanf("%d",&total);
    res=printgame(a,total);
    while(1)
    {
        printf("\n");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 8:
        {
            res=upmove(a);
            break;
        }
        case 2:
        {
            res=downmove(a);
            break;
        }
        case 4:
        {
            res=leftmove(a);
            break;
        }
        case 6:
        {
            res=rightmove(a);
            break;
        }
        default:
            printf("enter a valid choice\n");
        }
        if(res==-1 || res==100)
        {
            printf("want to play another??\n");
            printf("yes --> 1\nno --> 0\n" );
            scanf("%d",&chance);
            if(chance==0)
                break;
            else
            {
                printf("You wanna play upto\n");
                printf("16  32  64  128  256  512  1024  2048 4096?\n");
                scanf("%d",&total);
                for(i=0; i<4; i++)
                {
                    for(j=0; j<4; j++)
                    {

                        a[i][j]->flag=0;
                        a[i][j]->key=0;
                    }
                }
                res= printgame(a,total);
                continue;
            }
        }

    }
}
