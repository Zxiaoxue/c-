/*************************************************************************
	> File Name: Test2.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 16 Jun 2017 01:23:03 AM PDT
 ************************************************************************/
//输入n,求y1=1!+3!+...m!(m是小于等于n的最大奇数)
//y2=2!+4!+...p!(p是小于等于n的最大偶数)。)

#include<iostream>
using namespace std;

int main()
{
	int num = 0;
	cin>>num;
	int sum_e = 0;
	int sum_o = 0;
	int i,j,sum1,sum2;

	if(num >= 1)
	{
		sum1 = 1;
		sum_e = 1;
	}
	if(num >= 2)
	{	
		sum2 = 2;
		sum_o = 2;
	}

	for(i=3,j=4; (i<=num)||(j<=num); i+=2,j+=2)
	{
		if(i<=num)
		{
			sum1 = sum1*i*(i-1);
			sum_e += sum1;
		}
		if(j<=num)
		{
			sum2 = sum2*j*(j-1);
			sum_o += sum2;
		}
	}
	cout<<sum_e<<endl<<sum_o<<endl;
	return 0;
}

