#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>


//void Insertsort(int *a,size_t size)
//{
//	assert(a);
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	for (i = 0; i < size; ++i)
//	{
//		j = i;
//		tmp = a[j + 1];
//		while (j >= 0 && a[j] < tmp)
//		{
//			a[j + 1] = a[j];
//			j--;
//		}
//		a[j+1] = tmp;
//	}
//
//}

//void BubbleSort(int *a,size_t size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	int flag = 0;
//	assert(a);
//	for (i = 0; i < size - 1; i++)
//	{
//		flag = 0;
//		for (j = 0; j < size - i - 1; j++)
//		{
//			if (a[j]>a[j + 1])
//			{
//				tmp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = tmp;
//				flag = 1;
//			}
//		}
//		if (flag == 0)
//		{
//			return;
//		}
//	}
//}

//void BubbleSort(int *a, size_t size)
//{
//		int i = 0;
//		int j = 0;
//		int tmp = 0;
//		int flag = 0;
//		int pos = 0;
//		int k = size-1;
//		assert(a);
//		for (i = 0; i < size - 1; i++)
//		{
//			flag = 0;
//			for (j = 0; j < k; j++)
//			{
//				if (a[j]>a[j + 1])
//				{
//					tmp = a[j];
//					a[j] = a[j + 1];
//					a[j + 1] = tmp;
//					pos = j;
//					flag = 1;
//				}
//			}
//			k = pos;
//			if (flag == 0)
//			{
//				return;
//			}
//		}
//	}
//

//void SelectSort(int *a, size_t size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	assert(a);
//	int min = 0;
//	for (i = 0; i < size ;i++)
//	{
//		min = i;
//		for (j = i; j < size; j++)
//		{
//			if (a[min] > a[j])
//			{
//				min = j;
//			}
//		}
//		tmp = a[min];
//		a[min] = a[i];
//		a[i] = tmp;
//
//	}
//}

void swap(int *a, int *b)
{
	int tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int particular(int *a, int left, int right)
{
	int key = a[left];
	int begin = left;
	int end = right - 1;
	int tmp = 0;
	assert(a);
	

	while (begin < end)
	{
		while (begin < end&&a[begin] < key)
		{
			begin++;
		}
		while (begin<end&&a[end]>key)
		{
			end--;
		}
		if (begin < end)
		{
			swap(&a[begin], &a[end]);
		}
	
	}
	if (a[begin]>a[end])
		{
			swap(&a[begin], &key);
		}
	return begin;

}

void QuickSort(int *a, int left, int right)
{
	int div = 0;
	assert(a);
	if (left >= right)
	{
		return;
	}
	 div = particular(a, left, right);
	QuickSort(a, 0, div);
	QuickSort(a, div+1, right);
}


void SelectSort(int *a, size_t size)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	assert(a);
	int min = 0;
	int max = size - 1;
	for (i = 0; i < size ;i++)
	{
		min = i;
		for (j = i; j < size; j++)
		{
			if (a[min] > a[j])
			{
				min = j;
			}
			if (a[max] < a[j])
			{
				max = j;
			}
		}
		
		//_swap(a[min], a[i]);
		tmp = a[min];
		a[min] = a[i];
		a[i] = tmp;

		tmp = a[max];
		a[max] = a[size - 1];
		a[size - 1] = tmp;

	}
}


int main()
{
	int i = 0;
	int arr[] = { 1, 9, 4, 2, 6, 5, 8, 0, 7, 3 };
	//SelectSort(&arr, 10);
	//Insertsort(&arr,10);
	//BubbleSort(&arr, 10);

	QuickSort(&arr, 0, 10);

	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	system("pause");
	return 0;
}