//��һ�£���һ�� 
//p6 1.4.1 ����Ļ�����This is a c program.
//p8 eg:1.2 ����������֮��
//p8 eg:1.3 �����������еĽϴ���
//��һ��ϰ��
//p15 1 ʲô�ǳ���ʲô�ǳ�����ƣ�
//����һ��������ʶ���ִ�е�ָ��
//������ƣ���ȷ�����񵽵õ���д���ĵ���ȫ����
//p15 5


//p15 6
#include <stdio.h>

void Test4()
{
	int a, b, sum;
	printf("����������������");
	scanf("%d %d", &a, &b);
	sum = a + b;
	printf("%d\n", sum);
	return 0;
}
*/

void Test3()
{
	int a, b;
	printf("����������������");
	scanf("%d %d", &a, &b);
	if (a>b)
		printf("%d\n", a);
	else
		printf("%d\n", b);
	return;
}

void Test2()
{
	int  max(int a, int b);
	int a, b, c;
	printf("����������������");
	scanf("%d %d", &a, &b);
	c = max(a, b);
	printf("�ϴ�����%d\n", c);
	return 0;
}


int max(int a, int b)
{
	int c;
	if (a>b)
		c = a;
	else
		c = b;
	return c;
}
void Test()
{
	int a, b, c;
	int max;
	printf("����������������");
	scanf("%d %d %d", &a, &b, &c);
	max = (((a>b) ? a : b)>c) ? ((a>b) ? a : b) : c;
	printf("max=%d\n", max);
}
void Test1()
{
	int i;
	for (i = 0; i <= 30; i++)
		printf("*");
	printf("\n");
	printf("V e r y   g o o d !\n");
	for (i = 0; i <= 30; i++)
		printf("*");
	printf("\n");
}

int main()
{
	Test();
	system("pause");
	return 0;
}


