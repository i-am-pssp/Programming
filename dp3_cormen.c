#include<stdio.h>
void printLCS(char b[][100],char X[],int i,int j)
{
    if(i==0 || j==0)
        return ;
    if(b[i][j]=='s')
    {
        printLCS(b,X,i-1,j-1);
        printf("%c",X[i]);
    }
    else if(b[i][j]=='l')
    {
        printLCS(b,X,i,j-1);
    }
    else
    {
        printLCS(b,X,i-1,j);
    }
}
void lcs(char X[],char Y[],int x,int y)
{
  int c[100][100],i,j;
  char b[100][100];

  for(i=0;i<=x;i++)
    c[i][0]=0;
    for(i=0;i<=y;i++)
    c[0][i]=0;
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=y;j++)
        {

            if(X[i]==Y[j])
            {
            c[i][j]=1+c[i-1][j-1];
               b[i][j]='s';
            }
            else
            {
                if(c[i-1][j]>=c[i][j-1])
                {
                    c[i][j]=c[i-1][j];
                    b[i][j]='t';
                }
                else
                {
                    c[i][j]=c[i][j-1];
                    b[i][j]='l';
                }

            }
        }
    }
  printLCS(b,X,x,y);
}

int main()
{
    char X[100],Y[100];int x=0,y=0,i=0,j,m,n;
    printf("X=");
    scanf("%s",X);
     printf("Y=");
    scanf("%s",Y);
     while(X[i]!='\0')
       {
          x++;i++;
       }
       i=0;
     while(Y[i]!='\0')
     {
         y++; i++;
     }m=x;n=y;
     while(m>=1)
     {
         X[m]=X[m-1];
         m--;
     }
      while(n>=1)
     {
         Y[n]=Y[n-1];
         n--;
     }
    lcs(X,Y,x,y);
}
