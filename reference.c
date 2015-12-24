#include<stdio.h>
int main()
{
    long long int t,loopcount=1,n,i,j;
    long long int sum;
    scanf("%lld",&t);
    while(t--)
    {
    	loopcount=1; sum=0;
        scanf("%lld",&n);
        int arr[n+1];
        for(i=1;i<=n;i++)
           scanf("%lld",&arr[i]);
         j=1;
        while(j<n)
        {
            if(arr[j]<=arr[j+1])
            {
                loopcount++;
                j++;
                if(j==n&&loopcount>=2)
                {
                    sum+=((loopcount)*(loopcount+1))/2 -loopcount;
                }
            }
            else
            {
                if(loopcount>=2)
                {
                    sum+=((loopcount)*(loopcount+1))/2 -loopcount;

                }
                loopcount=1;
                j++;
            }
        }
printf("%lld\n",sum+n);
}
}
