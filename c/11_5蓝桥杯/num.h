#pragma once

#include <iostream>
using namespace std;

//输入两个正整数X,Y,求出[X,Y]内被除3余1并且被除5余3的整数的和
void Test1()
{
	int a,b,c,sum;
	scanf("%d %d",&a,&b);
	sum=0;
	c=a;

	do
	{
		for(c=a;c<=b;c++)
			if (c%3==1&&c%5==3)
			{ 
				sum=sum+c;

			}

	}
	while(c<=b&&c>=a);

	printf("%d",sum);

}