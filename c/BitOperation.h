#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//��������һ�ĸ���
//��ʵ��һ������������һ��������������������Ʊ�ʾ��1�ĸ���


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

//��һ������ж�һ�������ǲ���2�������η���һ�����������2�������η���
//��ô���Ķ����Ʊ�ʾ������ֻ��һλ��1������������λ����0������ǰ�������
//�����������ȥһ�����Լ��룬���������Ψһ��1�ͻ���0
bool IfTwoPower(int n)
{
	if (!(n&(n - 1)))
		return true;

	return false;
}


//������������m��n��������Ҫ�ı�m�Ķ����Ʊ�ʾ�еĶ���λ���ܵõ�n��
//1�����������������2��ͳ���ֻ�����1�ĸ���

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
//ʵ��һ8bitλ���ݵ�ָ��λ����0����1����������������λ����

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
//��һ�����飬����ֻ��1������ֻ����һ�Σ��������־�����2�Σ��ҳ��������

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


//��һ�����飬����ֻ��1������ֻ����һ�Σ��������־�����3�Σ��ҳ��������
int FindOnlyFromTwo(int a[], int len)
{

}


//��һ�����飬ֻ���������ֽ�����һ�Σ��������־�����2�Σ�
//�ҳ�����һ��������һ�ε�����

/*���������ֻ����һ�ε����֣��趨Ϊa,b��
Ҳ��Ӧ����򣬵�������Ԫ��ȫ�����Ľ��x=a^b����Ϊa,b�ǲ���ͬ�����֣�
���x�϶���Ϊ0������x���ӵ�λ����λ��ʼ���ҵ���һ��bitλΪ1��λ���趨Ϊ��mλ��
�����mλ��bit�϶�����a��������b��������ͬʱa,b�ĵ�mλ���ӵ͵���λ����Ϊ1��
�������Ϳ��Ը��������mλ�Ϳ��԰������Ϊ�������֣�һ��Ϊ��mλΪ0��һ��Ϊ��mλΪ1.
�������Ͱ�����ֽ����������������ֻ����һ�ε�������*/


int get_first_position(int num)
 {//�ӵ�λ��ʼ�ҵ���һ��λ1��bitλ  
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
{//�жϸ���������λ�õ�bitλ�Ƿ�Ϊ1  
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

