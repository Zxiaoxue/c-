#pragma once

#include <iostream>
using namespace std;

//��������������X,Y,���[X,Y]�ڱ���3��1���ұ���5��3�������ĺ�
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