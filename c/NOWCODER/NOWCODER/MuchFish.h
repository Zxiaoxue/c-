#include<iostream>
using namespace std;


void Test()
{

	int minsize, maxsize, n, fishsize, count =0;

	cin>>minsize>>maxsize>>n;
	int fish[10001] = {0};
	for(int i = 1; i<=n; i++)
	{
		cin>>fishsize;
		//ͳ�ƷŽ�ȥ����ᱻ�Ե���
		for(int j = 2*fishsize; j<=maxsize && j<=10*fishsize; j++)
		{
			fish[j] = 1;
		}
		//ͳ�ƻ�Ե�������
		for(int j = fishsize/2; j>=minsize && j>=fishsize/10; j--)
		{
			fish[j] = 1;
		}
	}
	
	for(int i = minsize; i<maxsize; i++)
	{
		if(fish[i] == 0)
			count++;
	}
	cout<<count<<endl;
}




