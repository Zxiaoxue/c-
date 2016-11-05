#include <iostream>
using namespace std;
#include <math.h>

//输入一个正整数n (1≤ n ≤6),再输入一个n 行n列的矩阵，
//找出该矩阵中绝对值最大的元素以及它的行下标和列下标。
void Test2()
{
	int n;
	int i,j;
	int max=0;
	int a[6][6];
	int c, d;
	scanf("%d",&n);
	for(i=0;i<n;i++)   
	{   
		for(j=0;j<n;j++)   

		{   
			scanf("%d",&a[i][j]);    
			if(abs(a[i][j])>=max)    
			{   
				max=abs(a[i][j]);
				c = i;          
				d = j;          
			}   
		}   
	}  
}