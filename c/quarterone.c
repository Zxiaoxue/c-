//第一章，第一节 
//p6 1.4.1 在屏幕上输出This is a c program.
//p8 eg:1.2 求两个整数之和
//p8 eg:1.3 求两个整数中的较大者
//第一章习题
//p15 1 什么是程序？什么是程序设计？
//程序：一组计算机能识别和执行的指令
//程序设计：从确定任务到得到，写出文档的全过程
//p15 5


//p15 6
#include <stdio.h>

void Test4()
{
	int a, b, sum;
	printf("请输入两个整数：");
	scanf("%d %d", &a, &b);
	sum = a + b;
	printf("%d\n", sum);
	return 0;
}
*/

void Test3()
{
	int a, b;
	printf("请输入两个整数：");
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
	printf("请输入两个整数：");
	scanf("%d %d", &a, &b);
	c = max(a, b);
	printf("较大数：%d\n", c);
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
	printf("请输入三个整数：");
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


