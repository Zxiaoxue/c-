#include <iostream>
using namespace std;
#include<string>

//������
/*ͳ��һ���ַ�����'*'�ĸ�����
ͬʱ�����еġ� * ���ƶ����ַ�����ǰ�棬����ַ������пո���ɾ�����еĿո�*/ 
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