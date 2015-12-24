#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct array
{
    char str[100];
} array;
void part1(char str[],int n)
{
    if(n==1)
    {
        printf("k=1\n");
        printf("substring is %c",str[0]);
    }
    int index[100],i=0,j,k=0,l;
    char p;
    p=str[0];
    while(str[i]!='\0')
    {
        i++;
        if(i<=(n-1) && p==str[i])
        {
            index[k]=i-1;
            k++;
        }
        p=str[i];
    }
    if(k==0)
    {
           printf("k=%d\n",k+1);
            printf("substring is %s",str);
            return ;
    }
    k++;
    printf("k=%d\n",k);
    printf("substrings are\n");
    i=0;
    for(j=0; j<k-1; j++)
    {
        if(j==0)
        {
            for(l=0; l<=index[j]; l++)
            {
                printf("%c",str[l]);
            }
            printf("\n");
            continue;
        }
        for(l=index[j-1]+1; l<=index[j]; l++)
        {
            printf("%c",str[l]);

        }
        printf("\n");
    }
    for(l=index[j-1]+1; l<n; l++)
    {
        printf("%c",str[l]);
    }
}
void part2(char s[],int n)
{
    char p,q;
    array a[100];
    int i=0,l=0,j=n-1,k,x,y,maxlen=0;
    printf("*");
    for(k=1; k<=(n-2); k++)
    {
       //printf("k=%d\n",k);
       if(k==0)
        {
            p=s[k+1];
            s[k+1]='\0';
            strcpy(a[l].str,s+i);

            // printf("%s\n",a[l].str);
            l++;
            s[k+1]=p;
        }
        if(s[k]==s[k-1])
        {
        x=k-2;
        y=k+1;
        while(x>=0 && y<=(n-1))
        {
            if(s[x]==s[y])
            {
                x--;y++;
            }
            else
                break;
        }
         p=s[y];
            s[y]='\0';
            strcpy(a[l].str,s+x+1);
           //  printf("%s\n",a[l].str);
            l++;
            s[y]=p;

        }
        if(s[k-1]==s[k+1])
        {
            x=k-2;y=k+2;
            while(x>=0 && y<=(n-1))
        {
            if(s[x]==s[y])
            {
                x--;y++;
            }
            else
                break;
        }
         p=s[y];
            s[y]='\0';
            strcpy(a[l].str,s+x+1);

            // printf("%s\n",a[l].str);
            l++;
            s[y]=p;

        }
    }
    l=0;
    for(i=0;i<n;i++)
    {
       // printf("%s\n",a[i].str);
       if(strlen(a[i].str)>=maxlen)
       maxlen=strlen(a[i].str);
    }
    printf("max length=%d\n",maxlen);
    for(i=0;i<n;i++)
    {
        if(maxlen==strlen(a[i].str))
            printf("%s\n",a[i].str);
    }
}
int main()
{
    int n,i;
    char str[100],p,s[100];

    printf("n=");
    scanf("%d",&n);
    printf("\nstring=");
    scanf("%s",str);
    for(i=0; i<n; i++)
    {
        s[i]=str[i];
    }
    part1(str,n);
   // printf("\n");
   printf("part2\n");
    part2(s,n);
}
