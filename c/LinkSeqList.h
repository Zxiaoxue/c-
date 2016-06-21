#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 1000
typedef int DataType;

typedef struct SeqList
{
	DataType array[MAX_SIZE];
	size_t size;
}SeqList;

void PushBack(SeqList *pSeq, DataType x);
void PopBack(SeqList *pSeq);
void InitSeqList(SeqList *pSeq);
void PushFront(SeqList *pSeq, DataType x);
void PopFront(SeqList *pSeq);
void Insert(SeqList *pSeq,int pos,DataType x);
void Swap(DataType a, DataType b);

int Find(SeqList* pSeq, size_t pos, DataType x);
void Erase(SeqList* pSeq, size_t pos);
int Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);

void Bubblesort(SeqList* pSeq);
void Selectsort(SeqList* pSeq);
void Selectsort_OP(SeqList* pSeq);
void Quiksort(SeqList* pSeq);
int Binarysearch(SeqList* pSeq,DataType x);


 
void InitSeqList(SeqList *pSeq)
{
	assert(pSeq);
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}
int Find(SeqList* pSeq, size_t pos, DataType x)
{
	int i = 0;
	assert(pSeq);
	for (; i < pSeq->size; ++i)
	{
		if (pSeq->array[i] == x)
		{
			return i;
		}
	}
	return -1;
}

void Erase(SeqList* pSeq, size_t pos)
{
	assert(pSeq);
	if (pSeq->size<0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	assert(pos < pSeq->size);
	int i = pos;
	for (; i < pSeq->size; i++)
	{
		pSeq->array[i] = pSeq->array[i + 1];
	}
	--(pSeq->size);
}

void PushBack(SeqList *pSeq, DataType x)
{
	assert(pSeq);
	if (pSeq->size >= MAX_SIZE)
	{
		printf("The SeqList is Full.\n");
		return;
	}
	pSeq->array[pSeq->size++] = x;
}

void PopBack(SeqList *pSeq)
{
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("The SeqList is NULL\n");
		return;
	}
	pSeq->array[pSeq->size] = 0;
	--pSeq->size;
}

void PushFront(SeqList *pSeq, DataType x)
{
	int begin = pSeq->size;
	assert(pSeq);
	if (pSeq->size >= MAX_SIZE)
	{
		printf("The SeqList is Full.\n");
		return;
	}
	for (; begin >= 0; --begin)
	{
		pSeq->array[begin] = pSeq->array[begin - 1];
	}
	pSeq->array[0] = x;
	pSeq->size++;
}

void PopFront(SeqList* pSeq)
{
	int begin = 0;
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("The SeqList is NULL");
		return;
	}
	for (; begin <= pSeq->size; begin++)
	{
		pSeq->array[begin] = pSeq->array[begin + 1];
	}
	pSeq->size--;
}
void Insert(SeqList* pSeq, int pos, DataType x)
{
	int begin = pSeq->size-1;
	assert(pSeq);
	assert(pos <= pSeq->size);
	if (pos >= MAX_SIZE)
	{
		printf("The SeqList is Full");
		return;
	}
	for (; begin >= pos; begin--)
	{
		pSeq->array[begin+1] = pSeq->array[begin];
	}
	pSeq->array[pos] = x;
	pSeq->size++;
}

void Printf(SeqList* pSeq)
{
	assert(pSeq);
	size_t i = 0;
	for (; i < pSeq->size; ++i)
	{
		printf("%d ",pSeq->array[i]);
	}
}

void Swap(DataType* a, DataType* b)
{
	DataType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int Remove(SeqList* pSeq, DataType x)
{
	int pos;
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return 0;
	}
	pos = Find(pSeq, 0, x);
	if (pos != -1)
	{
		Erase(pSeq, x);
	}
	return pos;
}
//void RemoveAll(SeqList* pSeq, DataType x)
//{
//	int pos;
//	assert(pSeq);
//	if (pSeq->size <= 0)
//	{
//		printf("The SeqList is empty\n");
//		return;
//	}
//	pos = Find(pSeq, 0, x);
//	while (pos != -1)
//	{
//		Erase(pSeq, pos);//~~~~~~~~~~~~~~~~~~
//		pos = Find(pSeq, pos,x);
//	}
//}

void RemoveAll(SeqList* pSeq, DataType x)
{
	int count = 0;
	int begin = 0;
	assert(pSeq);
	for (; begin < pSeq->size; ++begin)
	{
		if (pSeq->array[begin] == x)
		{
			++count;
		}
		else
		{
			pSeq->array[begin-count] = pSeq->array[begin];
		}
	}
	pSeq->size -= count;
}

void Bubblesort(SeqList* pSeq)//冒泡排序
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (; i < pSeq->size;i++)
	{
		for (j = 0; j < pSeq->size - i; j++)
		{
			if (pSeq->array[j] < pSeq->array[j - 1])
			{
				DataType temp;
				temp = pSeq->array[j - 1];
				pSeq->array[j-1] = pSeq->array[j] ;
				pSeq->array[j] = temp;
			}
		}
	}

}

void Selectsort(SeqList* pSeq)//选择排序~~~~~~~~~~~~~~~~~~~~~~~~
{	
	assert(pSeq);
	int i = 0;
	int j = 0;
	int min = 0; 
	for (j = 0; j < pSeq->size - 1; ++j)
	{
		min = j;
		for (i = j + 1; i < pSeq->size; ++i)
		{
			if (pSeq->array[i] < pSeq->array[min])
			{
				min = i;
			}
		}
		Swap(&pSeq->array[min], &pSeq->array[j]);
	}
	
}

void Selectsort_OP(SeqList* pSeq)
{	
	int i = 0;
	int min = 0;
	int max = 0;
	int left = 0;
	int right = pSeq->size - 1;
	assert(pSeq);
	while (left < right)
	{
		min= left;
		max = right;
		for (i = left; i <= right; ++i)
		{
			if (pSeq->array[i] < pSeq->array[min])
			{
				Swap(&pSeq->array[i], &pSeq->array[left]);
			}
			if (pSeq->array[i] > pSeq->array[max])
			{
				Swap(&pSeq->array[i], &pSeq->array[right]);
			}
		}
		left++;
		right--;
	}
}

void Quiksort(SeqList* pSeq)
{
	assert(pSeq);

}

int Binarysearch(SeqList* pSeq, DataType x)
{
	assert(pSeq);
	int left = 0;
	int right = pSeq->size - 1;
	while (left <= right)
	{
		int mid = left - (left - right) / 2;
		if (x < pSeq->array[mid])
		{
			right = mid;
		}
		else if (x > pSeq->array[mid])
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}



//链表
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef  int DataType;

typedef struct SListNode
{
	DataType data;           //数据
	struct SListNode* next;  //指向下一个节点的指针
}SListNode;

//void PushBack(SListNode* & pHead, DataType x);
//void PopBack(SListNode* & pHead);
//void PushFront(SListNode* & pHead, DataType x);
//void PopFront(SListNode* & pHead);
//void DestorySList(SListNode* & pHead);
//SListNode* buyNode(DataType x);
//SListNode* Find(SListNode* pHead, DataType x);
//void Insert(SListNode* pos, DataType x);
//void Erase(SListNode* pHead, SListNode* pos);
//void DelNonTailNode(SListNode* pos);


void Print(SListNode* head)
{
	SListNode* cur = head;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL");
	printf("\n");
}


SListNode* Buynode(DataType x)
{
	SListNode* temp;
	temp = (SListNode*)malloc(sizeof(SListNode));
	temp->data = x;
	temp->next = NULL;
	return temp;
}


void DestorysList(SListNode* & phead)
{
	SListNode* cur = phead;
	while (cur)
	{
		SListNode* temp = cur;
		cur = cur->next;
		free(temp);
		temp = NULL;
	}
}


void PushBack(SListNode* & phead, DataType x)
{
	//1.空
	//2.不空
	if (phead == NULL)
	{
		phead = Buynode(x);
	}
	else
	{
		SListNode* tail = phead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = Buynode(x);
	}
}

void PopBack(SListNode* & phead)
{
	//1.空
	//2.一个节点
	//3.多节点
	if (phead == NULL)
	{
		printf("the slist is empty\n");
		return;
	}
	else if (phead->next == NULL)
	{
		free(phead);
		phead = NULL;
	}
	else
	{
		SListNode* tail = phead;
		SListNode* prev = NULL;

		while (tail->next != NULL)
		{

			prev = tail;
			tail = tail->next;
		}

		free(tail);
		prev->next = NULL;
	}
}

void PushFront(SListNode* & phead, DataType x)
{
	/*1.空
	2.不空*/
	if (phead == NULL)
	{
		phead = Buynode(x);
	}
	else if (phead != NULL)
	{
		SListNode* cur = Buynode(x);
		cur->next = phead;
		phead = cur;
	}
}

void PopFront(SListNode* & phead)
{
	if (phead == NULL)
	{
		return;
	}
	else if (phead->next == NULL)
	{
		free(phead);
		phead = NULL;
	}
	else if (phead != NULL)
	{
		SListNode* cur = phead;
		phead = phead->next;
		free(cur);
		cur = NULL;
	}
}

SListNode* Find(SListNode* phead, DataType x)
{
	SListNode* cur = phead;
	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}

		cur = cur->next;
	}
	return NULL;
}

void Insert(SListNode* pos, DataType x)
{
	assert(pos);

	SListNode* temp = Buynode(x);
	temp->next = pos->next;
	pos->next = temp;

}
void Erase(SListNode* phead, SListNode* pos)
{
	assert(pos);
	assert(phead);
	if (phead == pos)
	{
		phead = phead->next;
		free(pos);
		pos = NULL;
	}
	SListNode* prev = phead;
	while (prev)
	{
		if (prev->next == pos)
		{
			prev->next = pos->next;
			free(pos);
			pos = NULL;
			break;
		}
		prev = prev->next;
	}
}
//////////////////////////////////////////////////////////////////////
//冒泡排序
void Bubble(SListNode* pHead)
{
	int exange = 0;
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	SListNode* prev = pHead;
	SListNode* cur = pHead->next;
	SListNode* Tail = NULL;
	while (Tail != pHead)
	{
		cur = pHead->next;
		prev = pHead;
		while (cur != Tail)
		{
			if (prev->data > cur->data)
			{
				DataType x;
				x = cur->data;
				cur->data = prev->data;
				prev->data = x;
			}
			prev = cur;
			cur = cur->next;
		}
		Tail = prev;
	}
}

//删除一个无头单链表的非尾节点
void DelNonTailNode(SListNode* pos)
{
	assert(pos);
	assert(pos->next);

	SListNode* del = pos->next;
	pos->data = del->data;
	pos->next = del->next;
	free(del);
	del = NULL;
}


//在无头单链表的非头节点插入一个节点
void InsertNonTailNode(SListNode* pos, DataType x)
{
	assert(pos);
	SListNode* cur = Buynode(pos->data);
	SListNode* temp = pos->next;
	cur->next = temp;
	pos->next = cur;
	pos->data = x;
}


//查找单链表的中间节点并只能遍历一次链表(快慢指针)

SListNode* FindMidNode(SListNode* pHead)
{
	assert(pHead);

	if (pHead->next == NULL)
	{
		return pHead;
	}
	else
	{
		SListNode* slow = pHead;
		SListNode* fast = pHead;
		/*	while (fast)
		{
		if (fast->next)
		{
		fast = fast->next->next;
		}
		else
		{
		break;
		}
		slow = slow->next;
		}*/
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
	return NULL;
}

//查找链表的倒数第k个节点，且只能遍历链表一次

SListNode* FindNode(SListNode* pHead, int k)
{
	assert(pHead);
	assert(k >= 0);

	SListNode* slow = pHead;
	SListNode* fast = pHead;
	//有问题
	/*while (fast && fast->next)
	{
	while (k--)
	{
	fast = fast->next;
	}
	fast = fast->next;
	slow = slow->next;
	}*/
	while (fast && --k)
	{
		fast = fast->next;
		if (fast == NULL)
		{
			return NULL;
		}
	}

	while (fast->next)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

//从尾到头打印单链表

void PrintTailToHead(SListNode* pHead)
{
	if (pHead == NULL)
	{
		return;
	}
	else
	{
		PrintTailToHead(pHead->next);
		printf("%d ", pHead->data);
	}
}


//逆置单链表   很重要
SListNode*  Reverse(SListNode* pHead)
{
	SListNode* cur = pHead;
	SListNode* newHead = NULL;

	while (cur)
	{
		SListNode* temp = cur;
		cur = cur->next;

		temp->next = newHead;
		newHead = temp;
	}
	return newHead;
}


//单链表实现约瑟夫环
//运行时先构造环，注意在代码结尾解环

SListNode* JosePhCycle(SListNode* pHead, int m)
{
	SListNode* cur = pHead;
	while (1)
	{
		if (cur == NULL)
		{
			return NULL;
		}
		else if (cur == cur->next)//只剩一个节点
		{
			return cur;
		}
		else
		{
			int x = m;
			while (--x)
			{
				cur = cur->next;
			}
			SListNode* del = cur->next;
			cur->data = del->data;
			cur->next = del->next;
			free(del);
			del = NULL;
		}
	}

}

//合并两个有序链表，合并后依然有序

SListNode* Meragelist(SListNode* pHead1, SListNode* pHead2)
{
	if (pHead1 == NULL)
	{
		return pHead2;
	}
	if (pHead2 == NULL)
	{
		return pHead1;
	}
	/*SListNode* newHead = pHead1->data < pHead2->data ? pHead1:pHead2;

	while (pHead1 == NULL || pHead2 == NULL)
	{
	if (pHead1->data < pHead2->data)
	{
	newHead = pHead1;
	pHead1 = pHead1->next;
	}
	else if (pHead1->data == pHead2->data)
	{
	newHead = pHead1;
	newHead->next = pHead2;
	pHead1 = pHead1->next;
	pHead2 = pHead2->next;
	}
	else
	{
	newHead = pHead2;
	pHead2 = pHead2->next;
	}
	newHead = newHead->next;
	newHead->next = NULL;
	}
	while (pHead1)
	{
	newHead->next = pHead1;
	pHead1 = pHead1->next;
	}
	while (pHead2)*/

	SListNode* newHead = NULL;
	SListNode* cur1 = pHead1;
	SListNode* cur2 = pHead2;
	if (cur1->data < cur2->data)
	{
		newHead = cur1;
		cur1 = cur1->next;
	}
	SListNode* Tail = newHead;
	while (cur1 && cur2)
	{
		if (cur1->data < cur2->data)
		{
			Tail->next = cur1;
			cur1 = cur1->next;
		}
		else
		{
			Tail->next = cur2;
			cur2 = cur2->next;
		}
		Tail = Tail->next;
		Tail->next = NULL;
	}
	if (cur1 != NULL)
	{
		Tail->next = cur1;
	}
	if (cur2 != NULL)
	{
		Tail->next = cur2;
	}
	return newHead;
}

//判断链表是否带环(可以用快慢指针解决)
bool IsSListCycle(SListNode* pHead)
{
	if (pHead == NULL)
	{
		printf("The SList is empty\n");
		return false;
	}
	SListNode* slow = pHead;
	SListNode* fast = pHead;

	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			SListNode* cur = slow;
			int length = 0;       //环的长度
			do
			{
				slow = slow->next;
				length++;

			} while (cur != slow);

			printf("%d\n", length);
			printf("The SList have cycle\n");
			return true;
		}
	}
	printf("The SList NO cycle\n");
	return false;
}

//环的入口点

SListNode* CycleEntry(SListNode* pHead)
{
	if (pHead == NULL)
	{
		printf("The SList is empty\n");
		return NULL;
	}
	SListNode* slow = pHead;
	SListNode* fast = pHead;

	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			return slow;
		}
	}
}

//链表是否相交，若相交，求交点（不带环）

SListNode* IsItersect(SListNode* pHead1, SListNode* pHead2)
{
	if (pHead1 == NULL)
	{
		printf("链表不相交\n");
		return pHead2;
	}
	if (pHead2 == NULL)
	{
		printf("链表不相交\n");
		return pHead1;
	}
	SListNode* cur1 = pHead1;
	SListNode* cur2 = pHead2;

	while (cur1 && cur2)
	{
		if (cur1 == cur2)
		{
			printf("链表相交，交点为：%d\n", cur1->data);
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;
}



