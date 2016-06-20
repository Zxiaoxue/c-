#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//二进制中一的个数
//请实现一个函数，输入一个整数，输出该数二进制表示中1的个数


int NumberOf1(int n)
{
	int count = 0;
	size_t i = 1;

	while (i)
	{
		if (n & i)
			count++;
		i = i << 1;
	}
	return count;
}

int NumberOf2(int n)
{
	int count = 0;

	while (n)
	{
		n = n&(n - 1);
		count++;
	}
	return count;
}

//用一条语句判断一个整数是不是2的整数次方，一个整数如果是2的整数次方，
//那么它的二进制表示中有且只有一位是1，而其他所有位都是0，根据前面分析的
//把这个整数减去一和它自己与，这个整数中唯一的1就会变成0
bool IfTwoPower(int n)
{
	if (!(n&(n - 1)))
		return true;

	return false;
}


//输入两个整数m和n，计算需要改变m的二进制表示中的多少位才能得到n，
//1，求这两个数的异或，2，统计抑或结果中1的个数

int CountChangeBit(int m, int n)
{
	int count = 0;
	int key = m^n;
	while (key)
	{
		key = key&(key - 1);
		count++;
	}
	return count;
}
//实现一8bit位数据的指定位的置0或置1操作，并保持其他位不变

void bit_set(unsigned char* p_data, unsigned char pos, int flag)
{
	assert(p_data);
	if (pos<0 || pos>8)
		return;
	if (flag == 1)
	{
		*p_data |= (flag << (pos-1));
	}
	else if (flag == 0)
	{
		*p_data &= ~(1 << (pos-1));
		//*p_data ^= (1 << (pos - 1));

	}

}
//有一个数组，其中只有1个数字只出现一次，其他数字均出现2次，找出这个数字

int FindOnlyFromTwo(int a[],int len)
{

	int ret = 0;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		ret = ret^a[i];
	}

	return ret;
}


//有一个数组，其中只有1个数字只出现一次，其他数字均出现3次，找出这个数字
int FindOnlyFromTwo(int a[], int len)
{

}


//有一个数组，只有两个数字仅出现一次，其他数字均出现2次，
//找出任意一个仅出现一次的数字

/*如果有两个只出现一次的数字，设定为a,b。
也是应用异或，但是数组元素全部异或的结果x=a^b，因为a,b是不相同的数字，
因此x肯定不为0。对于x，从低位到高位开始，找到第一个bit位为1的位置设定为第m位，
这个第m位的bit肯定来自a或者来自b，不可能同时a,b的第m位（从低到高位）都为1。
这样，就可以根据这个第m位就可以把数组分为两个部分，一组为第m位为0，一组为第m位为1.
这样，就把问题分解成了求两个数组中只出现一次的数字了*/


int get_first_position(int num)
 {//从低位开始找到第一个位1的bit位  
	int index = 1;
	int i = 0;
    while (i<32)
	{
		if ((num&(1 << i)) == (1 << i))
	           break;
		else
		{
			index++;
			i++;
		}
	}
	return index;
}
 int is_bit_one(int num, int index)
{//判断给定的索引位置的bit位是否为1  
   num = (num >> index);
    return num & 1;
 }
void get_two_unique_num(int *a, int n, int *num1, int *num2)
{
	   int exclusive_or_result = 0;
	   *num1 = 0;
	   *num2 = 0;
	     for (int i = 0; i<n; i++)
			 exclusive_or_result ^= a[i];
		 int index = get_first_position(exclusive_or_result);
		 for (int i = 0; i<n; i++)
		 if (is_bit_one(a[i], index))
			 (*num1) ^= a[i];
		 for (int i = 0; i<n; i++)
		 if (!is_bit_one(a[i], index))
			 (*num2) ^= a[i];
}

