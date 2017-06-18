/*************************************************************************
	> File Name: Test.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 18 Jun 2017 08:12:29 AM PDT
 ************************************************************************/

#include<stdio.h> 
     
int main()    
{    
        int i,N;    
        long long a[90];    
        while(~scanf("%d",&N))    
        {                 
                a[1]=1;    
                a[2]=2;    
                for(i=3;i<=N;i++)    
                        a[i]=a[i-1]+a[i-2];    
                printf("%lld\n",a[N]);    
        }    
             
        return 0;    
             
}    
