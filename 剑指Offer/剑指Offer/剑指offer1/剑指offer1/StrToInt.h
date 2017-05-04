#include <iostream>
#include <assert.h>
#include <math.h>
using namespace std;

#define MIN -2147483648
#define MAX 2147483647

int StrToInt(char* str)
{
	assert(str);
	long num = 0;
	int flag = 1;

	while(isspace(*str) != 0)
	{
		++str;
	}

	if(*str == '-')
		flag = -1;

	if(*str == '-' || *str == '+')
	{
		++str;
	}

	while(*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		if(flag == '-')
		{
			if(num > MAX || num < MIN)
				return 0;
		}
		++str;
	}
	return flag*num;
}