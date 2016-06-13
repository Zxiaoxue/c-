#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

enum state
{
	VALUE,
	UNVALUE
};

long long my_atoi(char *str)
{
	assert(str);
	int state = 0;
	int flag = 1;
	long long ret = 0;

	while (isspace(*str))
	{
		str++;
	}
	if (*str == '\0')
	{
		return ret;
	}
	if (*str == '+')
	{
		str++;
	}
	if (*str == '-')
	{
		flag = -1;
		str++;
	}
	while (*str)
	{
		state = VALUE;
		if (*str >= '0'&&*str <= '9')
		{
			ret = ret * 10 + (*str - '0') * flag;
			if (ret > INT_MAX || ret < INT_MIN)
			{
				ret = 0;
				break;
			}
			str++;
		}
		else
		{
			ret = 0;
			break;
		}
	}
	if (*str == '\0')
	{
		state = VALUE;
		return ret;
	}
}

void bit_set(unsigned char *p_data, unsigned char pos, int flag)
{
	assert(p_data);
	assert(pos <= 8);

	if (flag == 1)
	{
		*p_data |= (1 << (pos - 1));
	}
	else if (flag == 0)
	{
		*p_data ^= (1 << (pos - 1));

		//*p_data &= ~(1 << (pos - 1));
	}

	printf("%d\n", *p_data);

	return;
}

void _reserve(char *str, char *left, char *right)
{
	assert(str);
	assert(left);
	assert(right);

	while (left < right)
	{
		char tmp = 0;
		tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}

}

//void RightLoopMove(char *pStr, unsigned short steps)
//{
//	assert(pStr);
//	int len = strlen(pStr);
//	_reserve(pStr, pStr, pStr + len-1);
//	_reserve(pStr, pStr, pStr + steps - 1);
//	_reserve(pStr, pStr + steps, pStr + len - 1);
//	printf("%s\n", pStr);
//
//}

void RightLoopMove(char *pStr, unsigned short steps)
{
	assert(pStr);
	int len = strlen(pStr);
	int i = len - 1;
	while (steps--)
	{
		char tmp = *(pStr + len - 1);

		for (int i = len - 1; i >= 0; i--)
		{
			pStr[i] = pStr[i - 1];
		}
		pStr[0] = tmp;
	}
	printf("%s\n", pStr);
}



int main()
{
	/*char i = 15;
	bit_set(&i, 5, 1);*/

	char str[] = "abcdefghi";
	RightLoopMove(str, 3);

	//char *str = "-12345sgbdcsklk";
	//long long ret = atoi(str);
	//printf("%d\n", ret);


	system("pause");
	return 0;
}