#include<stdio.h>
#include<stdlib.h>
typedef struct index
{
    float key;
    int idx;
} index;
typedef struct max_idx  /*array to store maximum of effective p/t and prefix*/
{
    float max;
    int idx;
}max_idx;

typedef struct chain  /*defining chain*/
{
    int count,idx,flag;
    int p[50],t[50];
    float z[50];

} chain;
void merge(index arr[], int l, int m, int r) /*merge function taken from internet*/
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


void mergeSort(index arr[],int l, int r) /*mergesort taken from internet*/
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

    for(i=0; i<n; i++) /*calculating p/t values*/
    {
        div[i].key=(float)P[i]/T[i];
        div[i].idx=i;
    }
    mergeSort(div,0,n-1); /*sorting in nlogn time*/
    printf("+++OPTIMIZATION WITHOUT CONSTRAINTS\n");
    for(i=0; i<n; i++)
    {
        printf("Selecting Task %d (%d,%d) \n",div[i].idx,P[div[i].idx],T[div[i].idx]);
    }
    for(i=0; i<n; i++) /*calculating F values*/
    {
        for(j=0; j<=i; j++)
        {
            F[i]+=T[div[j].idx];
        }
    }
    for(i=0; i<n; i++) /*calculating objective function*/
    {
        obj+=P[div[i].idx]*F[i];
    }
    printf("minimized objective function is %d\n",obj);
}
void buildchains(chain c[],int P[],int T[],int m,int n)
{
    int i,j,k,x;
    for(i=0; i<m; i++) /*initializing chain variables*/
    {
        c[i].count=0;
        c[i].idx=i;
        c[i].flag=0;
    }
    for(i=0; i<n; i++)
    {
        printf("enter the chain number to which %d task should go\n",i);
        scanf("%d",&x);
        c[x].p[c[x].count]=P[i];
        c[x].t[c[x].count]=T[i];

        c[x].count++;
    }


    for(i=0; i<m; i++)  /*printing the chains*/
    {
        printf("Chain %d : ",i);
        for(j=0; j<c[i].count; j++)
        {
            printf(" (%d,%d) ",c[i].p[j],c[i].t[j]);
        }
        printf("\n");
    }
}
void sortchain(chain c[],int m, max_idx arr[]) /*function to sort max p/t values in each chain*/
{
    int i,j;
    chain temp;
    max_idx temp2;
    for (i=m-2; i>=0; --i)
    {
        for (j=0; j<=i; ++j)
        {
            if (arr[j].max < arr[j+1].max)
            {

                temp = c[j];  /*swapping chains and structures containing max and prefixes*/
                c[j] = c[j+1];
                c[j+1] = temp;
                temp2=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp2;
            }
        }
    }
}
float effective(chain c,int j) /*function to calculate p/t for each prefix*/
{
    int i,p_eff=0,t_eff=0;
    float result;
    for(i=0; i<=j; i++)
    {
        p_eff+=c.p[i];
        t_eff+=c.t[i];

    }
    result=(float)p_eff/t_eff;
    return result;
}

chain newchain(chain c,int j) /*function to replace old chain*/
{
    chain new;
    int i;
    for(i=0; i<c.count; i++)
    {
        new.p[i]=c.p[j];
        new.t[i]=c.t[j];
        new.count=c.count;
        new.idx=c.idx;
        new.z[i]=effective(new,i);
        new.flag=c.flag;
        j++;
    }
    return new;
}
void newtable(chain c[],chain ref[],int m) /*function to remove a task-completed chain and put remaining chains in a new table*/
{
    int i;
    for(i=0; i<m-1; i++)
    {
        c[i]=c[i+1];
        ref[c[i].idx].flag=ref[c[i+1].idx].flag;
    }
    c[m-1].count=0;
}

void optchain(chain c[],int m)
{
    printf("+++optimization satisfying chain constraints\n");
    int i,j=0,k,obj=0,F=0,ref_idx;
    max_idx  arr[50];
    float maximum;
    chain ref[100];
for(i=0; i<m; i++) /*calculating p/t of all prefixes of all chains*/
    {
        for(j=0; j<c[i].count; j++)
        {
            c[i].z[j]=effective(c[i],j);

        }
    }

    for(i=0; i<m; i++) /*storing max and prefix of each chain*/
    {
        maximum=c[i].z[0];
        for(j=0; j<c[i].count; j++)
        {
            if(c[i].z[j]>=maximum)
            {
                maximum=c[i].z[j];
                arr[i].idx=j;
            }

        }
        arr[i].max=maximum;
    }


    for(i=0; i<m; i++) /*copying table into a new table*/
    {
        ref[i]=c[i];
    }
    sortchain(c,m,arr);

    while(m>0)
    {
        k=0;

        while(k<=arr[0].idx) /*printing all tasks in prefix and calculating obj till the prefix*/
        {
            F+=ref[c[0].idx].t[k+ref[c[0].idx].flag];
            obj+=ref[c[0].idx].p[k+ref[c[0].idx].flag]*F;

            printf("Selecting task %d of chain %d (%d,%d)\n",k+ref[c[0].idx].flag,c[0].idx,ref[c[0].idx].p[k+ref[c[0].idx].flag],ref[c[0].idx].t[k+ref[c[0].idx].flag]);
            k++;
        }
        ref[c[0].idx].flag+=k;
        c[0].count-=k;
        if(c[0].count!=0)
            c[0]=newchain(c[0],k);
        else
        {
            newtable(c,ref,m);
            m--;
        }


        for(i=0; i<m; i++)
        {
            for(j=0; j<c[i].count; j++)
            {
                c[i].z[j]=effective(c[i],j);
            }
        }

        for(i=0; i<m; i++)
        {
            maximum=c[i].z[0];
            for(j=0; j<c[i].count; j++)
            {
                if(c[i].z[j]>=maximum)
                {
                    maximum=c[i].z[j];
                    arr[i].idx=j;
                }
            }
            arr[i].max=maximum;
        }
        sortchain(c,m,arr);

    }
    printf("minimzed objective function = %d\n",obj);

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
    optchain(c,m);
}

