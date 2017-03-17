#include<iostream>
using namespace std;


void replaceSpace(char* str, int length)
{
	int count = 0;
	for(int i = 0; i<length; i++)
	{
		if(str[i] == ' ')
		{
			count++;
		}
	}
	int newindex = length+2*count;
	char* index = str+length;
	while(index >= str)
	{
		if(*index == ' ')
		{
			str[newindex--] = '0';
			str[newindex--] = '2';
			str[newindex--] = '%';
		}
		else
			str[newindex--] = *index;
		
		index--;
	}
}