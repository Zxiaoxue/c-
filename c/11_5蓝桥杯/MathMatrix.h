#include <iostream>
using namespace std;
#include <math.h>

//����һ��������n (1�� n ��6),������һ��n ��n�еľ���
//�ҳ��þ����о���ֵ����Ԫ���Լ��������±�����±ꡣ
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