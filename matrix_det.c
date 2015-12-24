#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int deter(int **a,int i,int j)
{
    int **b,k,l,m,n,p=0,q,det=0;
    b=(int **)malloc((j-i)*sizeof(int *));
    for(k=i; k<j; k++)
        b[k]=(int *)malloc((j-i)*sizeof(int));
    if(i==j)
        return a[i][j];
    for(k=i; k<=j; k++)
    {
        p=0;
        for(m=i+1; m<=j; m++)
        {
            q=0;
            for(n=i; n<=j; n++)
            {
                if(n!=k)
                {
                    b[p][q]=a[m][n];
                    q++;
                }
            }
            p++;
        }
        det+=pow(-1,k)*a[i][k]*deter(b,i,j-1);
    }
    return det;
}
void adjoint(int **a,int n)
{
    int i,j,k,l,**b,**c,p,q,x,y;
    b=(int **)malloc((n-1)*sizeof(int *));
    for(k=0; k<n-1; k++)
        b[k]=(int *)malloc((n-1)*sizeof(int));
    c=(int **)malloc(n*sizeof(int *));
    for(k=0; k<n; k++)
        c[k]=(int *)malloc(n*sizeof(int));
    for(k=0; k<=(n-1); k++)
    {
        for(l=0; l<=(n-1); l++)
        {
            p=0;
            for(x=0; x<=(n-1); x++)
            {
                if(x!=k)
                {
                    q=0;
                    for(y=0; y<=(n-1); y++)
                    {
                        if(y!=l)
                        {
                            b[p][q]=a[x][y];
                            q++;
                        }
                    }
                    p++;
                }
            }
             c[k][l]=pow(-1,k+l)*deter(b,0,n-2);
        }
     }
    for(i=0;i<n;i++)
    {
       for(j=0;j<n;j++)
            printf("%4d",c[j][i]);
        printf("\n");
    }
}
int main()
{
    int n,i,j,det;
    printf("order=");
    scanf("%d",&n);
    int **a;
    a=(int **)malloc(n*sizeof(int *));
    for(i=0; i<n; i++)
        a[i]=(int *)malloc(n*sizeof(int));
    printf("enter elements\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            scanf("%d",&a[i][j]);
    }
    printf("matrix is \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%4d",a[i][j]);
        printf("\n");
    }
    det=deter(a,0,n-1);
    printf("final_det=%d\n",det);
    adjoint(a,n);
}
