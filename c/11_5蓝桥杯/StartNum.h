#include <iostream>
using namespace std;
#include<string>

//数星星
/*统计一个字符串中'*'的个数，
同时将所有的‘ * ’移动到字符串的前面，如果字符串中有空格，则删除所有的空格。*/ 
void Test3()
{
	string str;
	getline(cin,str);
	string str2;
	int count = 0;
	for(int i = 0;i < str.size();i++)
	{
		if(str[i] != ' ')
		{
			if(str[i] == '*')
				count++;
			else
				str2.push_back(str[i]);
		}
	}
	int num = count;
	while(count--)
		str2.insert(0,"*");

	cout<<str2<<endl;
	cout<<num<<endl;
}