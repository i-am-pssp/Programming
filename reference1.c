#include<stdio.h>
#include<stdlib.h>
typedef struct index
{
    float key;
    int idx;
} index;
typedef struct chain
{
    int count;
    int p[50],t[50];
float z[50];
} chain;
void merge(index arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    index L[n1], R[n2];
    for(i = 0; i < n1; i++)
    {
        L[i].key = arr[l + i].key;
        L[i].idx=arr[l+i].idx;
    }
    for(j = 0; j < n2; j++)
    {
        R[j].key = arr[m + 1+ j].key;
        R[j].idx=arr[m+1+j].idx;
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].key >= R[j].key)
        {
            arr[k].key = L[i].key;
            arr[k].idx=L[i].idx;
            i++;
        }
        else
        {
            arr[k].key = R[j].key;
            arr[k].idx=R[j].idx;
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k].key = L[i].key;
        arr[k].idx=L[i].idx;
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k].key = R[j].key;
        arr[k].idx=R[j].idx;
        j++;
        k++;
    }

}


void mergeSort(index arr[],int l, int r)
{
    int i;
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr,l, m, r);

    }
}
void  optnocons(int P[],int T[],index div[],int F[],int n)
{
    int i,j,obj=0;
    for(i=0; i<n; i++)
    {
        F[i]=0;
    }

    for(i=0; i<n; i++)
    {
        div[i].key=(float)P[i]/T[i];
        div[i].idx=i;
    }
    mergeSort(div,0,n-1);

    for(i=0; i<n; i++)
    {
        printf(" %d (%d,%d) \n",div[i].idx,P[div[i].idx],T[div[i].idx]);
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<=i; j++)
        {
            F[i]+=T[div[j].idx];
        }
    }
    for(i=0; i<n; i++)
    {
        obj+=P[div[i].idx]*F[i];
    }
    printf("minimized objective function is %d\n",obj);
}
void buildchains(chain c[],int P[],int T[],int m,int n)
{
    int i,j,x;
    for(i=0; i<m; i++)
    {
        c[i].count=0;

    }
    for(i=0; i<n; i++)
    {

        scanf("%d",&x);
        c[x].p[c[x].count]=P[i];
        c[x].t[c[x].count]=T[i];
        c[x].z[c[x].count]=(float)P[i]/T[i];
        c[x].count++;
    }
    for(i=0; i<m; i++)
    {
        printf("Chain %d : ",i);
        for(j=0; j<c[i].count; j++)
        {
            printf(" (%d,%d) ",c[i].p[j],c[i].t[j]);
        }
        printf("\n");
    }
}


int main()
{
    int n,i,j,m;
    index div[100];
    int P[100],T[100],F[100];
    chain c[100];
    printf("enter n\n");
    scanf("%d",&n);
    printf("enter Penalty and Load\n");
    for(i=0; i<n; i++)
    {
        scanf("%d%d",&P[i],&T[i]);
    }
    optnocons(P,T,div,F,n);
    printf("enter m value\n");
    scanf("%d",&m);
    buildchains(c,P,T,m,n);

}

