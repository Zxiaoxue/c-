#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


typedef  int DataType;

typedef struct SeqList
{
	DataType* array;   //数据块指针
	size_t size;       //当前有效数据个数
	size_t capicity;   //容量
}SeqList;

void InitSeqList(SeqList* pSeq);
void CheckCapicity(SeqList* pSeq);
void  PushBack(SeqList* pSeq, DataType x);
void  PopBack(SeqList* pSeq);
void  PushFront(SeqList* pSeq, DataType x);
void  PopFront(SeqList* pSeq);
void Print(SeqList* pSeq);

void Insert(SeqList* pSeq, size_t pos, DataType x);
int Find(SeqList* pSeq, size_t pos, DataType x);
void Erase(SeqList* pSeq, size_t pos);

void Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);



void InitSeqList(SeqList* pSeq)
{
	assert(pSeq);
	pSeq->array = (DataType*)malloc(sizeof(DataType)*3);
	pSeq->size = 0;
	pSeq->capicity = 3;
}

void CheckCapicity(SeqList* pSeq)
{
	if (pSeq->size >= pSeq->capicity)
	{
		pSeq->capicity = 2 * pSeq->capicity;
		pSeq->array = (DataType *)realloc(pSeq->array, pSeq->capicity*sizeof(DataType));
	}
}

void PushBack(SeqList* pSeq,DataType x)
{
	assert(pSeq);
	CheckCapicity(pSeq);
	pSeq->array[pSeq->size++] = x;
}

void  PopBack(SeqList* pSeq)
{
	assert(pSeq);
	pSeq->array[pSeq->size--] = 0;
}

void  PushFront(SeqList* pSeq, DataType x)
{
	int i = pSeq->size;
	assert(pSeq);
	CheckCapicity(pSeq);
	for (; i >= 0; i--)
	{
		pSeq->array[i] = pSeq->array[i-1];
	}
	pSeq->array[0] = x;
	pSeq->size++;
}

void  PopFront(SeqList* pSeq)
{
	int i = 0;
	assert(pSeq);
	for (; i <= pSeq->size; i++)
	{
		pSeq->array[i] = pSeq->array[i + 1];
	}
	pSeq->size--;
}

void Print(SeqList* pSeq)
{
	assert(pSeq);
	size_t i = 0;
	for (; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->array[i]);
	}
	printf("\n");
}

void Insert(SeqList* pSeq, size_t pos, DataType x)
{
	assert(pSeq);
	CheckCapicity(pSeq);
	for (size_t i = pSeq->size; i > pos; i--)
	{
		pSeq->array[i] = pSeq->array[i-1];
	}
	pSeq->array[pos] = x;
	pSeq->size++;
}


int Find(SeqList* pSeq,size_t pos, DataType x)
{
	size_t i = 0;
	assert(pSeq);
	for (; i < pSeq->size;i++)
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
	size_t i = pos;
	assert(pSeq);
	for (; i < pSeq->size; ++i)
	{
		pSeq->array[i] = pSeq->array[i+1];
	}
	--pSeq->size;
}

void Remove(SeqList* pSeq, DataType x)
{
	int pos = 0;
	assert(pSeq);
	if (pSeq->size)
	{
		printf("The SeqList is empty\n");
		return;
	}
	pos = Find(pSeq, 0, x);
	if (pos != -1)
	{
		Erase(pSeq, pos);
	}
}
void RemoveAll(SeqList* pSeq, DataType x)
{
	assert(pSeq);
	int count = 0;
	size_t begin = 0;
	for (; begin < pSeq->size; begin++)
	{
		if (pSeq ->array[begin] == x)
		{
			count++;
		}
		else
		{
			pSeq->array[begin - count] = pSeq->array[begin];
		}
	}
	pSeq->size -= count;
}


//#define _CRT_SECURE_NO_WARNINGS 1
//
//#include "SeqList.h"
//
//void Test1()
//{
//	SeqList s;
//	InitSeqList(&s);
//
//	PushBack(&s, 1);
//	PushBack(&s, 2);
//	PushBack(&s, 3);
//	PushBack(&s, 4);
//	PushBack(&s, 5);
//	PushBack(&s, 6);
//
//	PopBack(&s);
//	PopBack(&s);
//	PushFront(&s, 0);
//	PopFront(&s);
//
//	Print(&s);
//}
//void Test2()
//{
//	SeqList s;
//	InitSeqList(&s);
//
//	PushBack(&s, 1);
//	PushBack(&s, 2);
//	PushBack(&s, 3);
//	//PushBack(&s, 4);
//	PushBack(&s, 5);
//	PushBack(&s, 6);
//	Insert(&s, 3, 4);
//
//	Print(&s);
//}
//
//void Test3()
//{
//	SeqList s;
//	InitSeqList(&s);
//
//	PushBack(&s, 1);
//	PushBack(&s, 2);
//	PushBack(&s, 3);
//	PushBack(&s, 4);
//	PushBack(&s, 5);
//	PushBack(&s, 6);
//
//	/*int i = Find(&s, 3);
//	printf("%d ", i);*/
//	Erase(&s, 2);
//
//	Print(&s);
//
//
//}
//int main()
//{
//	Test3();
//	system("pause");
//	return 0;
//}


#include<stdio.h>
#include<stdlib.h>

#include<assert.h>

#define DataType int 
typedef struct SeqList
{
	DataType *data;// 定义一个指针指向这块空间
	int _capacity = 0;//空间大小
	int _size = 0;//有效数据的个数

}SeqList, *pSeqList;

void InitSeqList(pSeqList pSeq)
{
	assert(pSeq);
	pSeq->data = (DataType*)malloc(sizeof(DataType)* 3);
	pSeq->_size = 0;
	pSeq->_capacity = 3;
}

void CheckCapacity(pSeqList pSeq)
{
	assert(pSeq);
	if (pSeq->_capacity == pSeq->_size)
	{
		DataType* tmp = (DataType *)realloc(pSeq->data, sizeof(DataType)*(pSeq->_capacity * 2 + 3));
		if (tmp == NULL)
		{
			return;
		}
		else
		{
			pSeq->data = tmp;
			pSeq->_capacity = pSeq->_capacity * 2 + 3;
		}
	}


}
void PushBack(pSeqList pSeq, DataType x)
{
	CheckCapacity(pSeq);
	pSeq->data[pSeq->_size] = x;
	pSeq->_size++;
}
void PrintfList(pSeqList pSeq)
{
	int i = 0;
	for (i = 0; i < pSeq->_size - 1; i++)
	{
		printf("%d ", pSeq->data[i]);
	}
}

//void Test()
//{
//	SeqList seq;
//	InitSeqList(&seq);
//	PushBack(&seq, 1);
//	PushBack(&seq, 2);
//	PushBack(&seq, 3);
//	PushBack(&seq, 4);
//	PushBack(&seq, 5);
//	PushBack(&seq, 6);
//	PushBack(&seq, 7);
//	PrintfList(&seq);
//}
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}

