#include<stdio.h>
#include<stdlib.h>
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        char s[400],a[400];
        scanf("%s",s);
        int i,j;
        for(i=0,j=0; s[i]!='\0'; i++)
        {
            if(s[i]=='(')
                continue;
            else if(s[i]==')')
            {
                printf("%c",a[j]);
                j--;
            }
            else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='^' || s[i]=='/')
            {
                j++;
                a[j]=s[i];
            }
            else
            {
                printf("%c",s[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
