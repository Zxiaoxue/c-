#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int  Datatype;

typedef struct Complex
{
	Datatype data;
	Complex* next;
	Complex* redom;
}Complex, *pComplex;

pComplex BuyNode(Datatype x)
{
	pComplex tmp = (pComplex)malloc(sizeof(Complex));
	if (tmp)
	{
		tmp->data = x;
		tmp->next = NULL;
		tmp->redom = NULL;
	}
	return tmp;
}

void Printf(pComplex head)
{
	while (head)
	{
		printf("head:%d,redom->%d\n", head->data, head->redom->data);
		head = head->next;
	}
}


pComplex CopyComplexLinkList(pComplex head)
{
	pComplex newhead = head;
	pComplex tail = head;
	pComplex cur = head;

	while (cur)
	{
		pComplex tmp = BuyNode(cur->data);
		tmp->next = cur->next;
		cur->next = tmp;
		cur = cur->next->next;
	}
	cur = head;
	while (cur)
	{
		cur->next->redom = cur->redom;
		cur = cur->next->next;
	}

	cur = head;
	newhead = cur->next;
	while (cur && cur->next)
	{
		tail = cur->next;
		tail = tail->next;
		cur->next = cur->next->next;
		cur = cur->next;
	}
	return newhead;
}



void Test()
{
	pComplex c1 = BuyNode(1);
	pComplex c2 = BuyNode(2);
	pComplex c3 = BuyNode(3);
	pComplex c4 = BuyNode(4);
	pComplex c5 = BuyNode(5);

	c1->next = c2;
	c2->next = c3;
	c3->next = c4;
	c4->next = c5;

	c1->redom = c3;
	c2->redom = c4;
	c3->redom = c5;
	c4->redom = c1;
	c5->redom = c2;

	c1 = CopyComplexLinkList(c1);

	Printf(c1);


}
int main()
{
	Test();
	system("pause");
	return 0;
}