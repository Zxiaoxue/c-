#include<iostream>
using namespace std;
#include<string.h>
#include<vector>

#define MAX 1000
string w[MAX];
vector<string> t;

void Test()
{
	int num;
	while(cin>>num)
	{
		t.clear();
		int flag = 0;
		for(int j = 0; j<num; j++)
			cin>>w[j];
		for(int k = 0; k<num; k++)
		{
			for(int i = 0; i<t.size(); i++)
			{
				if(t[i].size() == 2*w[i].size())
				{
					if(t[i].find(w[i])== -1)
						flag = 1;
				}
			}
			if(flag == 1)
			{
			//重复待测试的单词，在查找子串
				string str(w[k]);
				str.append(w[k]);
	
				t.push_back(str);
			}
		}
		cout<<t.size()<<endl;
	}
	
}
