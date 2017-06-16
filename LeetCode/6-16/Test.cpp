/*************************************************************************
	> File Name: Test.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 16 Jun 2017 12:56:15 AM PDT
 ************************************************************************/
//输入一个整数，将其转换成八进制数输出。

#include <iostream>
#include <string.h>
using namespace std;

#define LEN 128

int main()
{
	int a = 0;
	int i = 0;
	int num[LEN];

	memset(num, 0, LEN);
	cin>>a;
	while(a > 0)
	{
		num[i] = a%8;
		a/=8;
		i++;
	}

	for(int j=i-1; j>=0; j--)
	{
		cout<<num[j];
	}
	cout<<endl;
	return 0;
}
