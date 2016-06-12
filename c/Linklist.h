#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;


typedef struct LinkNode
{
	DataType data;
	struct LinkNode* next;
}LinkNode, *pLinkNode;

typedef struct LinkList
{
	LinkNode* pHead;
}LinkList, *pLinkList;

void InitLinkList(pLinkList list)
{
	assert(list);
	list->pHead = NULL;
}

void Destory(pLinkList list)
{
	pLinkNode cur = NULL;
	assert(list);
	if (list->pHead == NULL)
	{
		return;
	}
	cur = list->pHead;
	while (cur)
	{
		pLinkNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;

	}
}

pLinkNode BuyNode(DataType x)
{
	pLinkNode newNode = (pLinkNode)malloc(sizeof(LinkNode));
	if (NULL == newNode)
	{
		printf("out of memory\n");
		return NULL;
	}
	newNode->next = NULL;
	newNode->data = x;
	return newNode;
}

void PrintList(pLinkList list)
{
	pLinkNode cur = NULL;
	assert(list);
	cur = list->pHead;

	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void PushBack(pLinkList list, DataType x)
{
	pLinkNode cur = NULL;
	assert(list);
	cur = list->pHead;
	pLinkNode newNode = BuyNode(x);
	if (list->pHead == NULL)
	{
		list->pHead = newNode;
	}
	else
	{
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}
void PopBack(pLinkList list)
{
	pLinkNode cur = NULL;
	pLinkNode prev = NULL;
	assert(list);
	cur = list->pHead;
	prev = NULL;
	if (cur == NULL)
	{
		printf("NULL");
	}
	else if (cur->next == NULL)
	{
		free(list->pHead);
		list->pHead = NULL;
	}
	else
	{
		while (cur->next != NULL)
		{
			prev = cur;
			cur = cur->next;
		}
		free(cur);
		cur = NULL;
		prev->next = NULL;
	}

}
void PushFront(pLinkList list, DataType x)
{
	pLinkNode cur = NULL;
	assert(list);
	cur = BuyNode(x);
	cur->next = list->pHead;
	list->pHead = cur;

}
void PopFront(pLinkList list)
{
	pLinkNode del = NULL;
	assert(list);
	del = list->pHead;
	list->pHead = list->pHead->next;
	free(del);
	del = NULL;

}
//void DestoryList(pLinkList list);
LinkNode* Find(pLinkList list, DataType x)
{
	pLinkNode cur = NULL;
	assert(list);
	cur = list->pHead;
	while (cur->next != NULL)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
void Insert(pLinkList list, LinkNode* pos, DataType x)
{
	pLinkNode cur = NULL;
	assert(list);
	//assert(pos);
	if (pos == NULL)
	{
		printf("没找到\n");
		return;
	}
	cur = BuyNode(x);
	cur->next = pos->next;
	pos->next = cur;


}
void Erase(pLinkList list, LinkNode* pos)//删pos节点
{
	pLinkNode del = NULL;
	assert(list);

	if (pos == NULL)
	{
		printf("无此节点\n");
		return;
	}
	//assert(pos);
	del = pos->next;
	del->next = del->next;
	free(del);
	del = NULL;

}

void Bubble(pLinkList list)
{
	pLinkNode cur = NULL;
	pLinkNode prev = NULL;
	pLinkNode tail = NULL;
	int exage = 0;
	assert(list);
	cur = list->pHead;
	if (list->pHead == NULL)
	{
		return;
	}
	while (list->pHead != tail)
	{
		prev = list->pHead;
		cur = prev->next;
		while (cur != tail)
		{
			exage = 0;
			if (cur->data < prev->data)
			{
				DataType x = cur->data;
				cur->data = prev->data;
				prev->data = x;
				exage = 1;
			}
			prev = cur;
			cur = cur->next;
		}
		tail = prev;
		if (exage == 0)
		{
			return;
		}
	}
}
