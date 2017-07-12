#include<iostream>
#include "List.h"
using namespace std;


void Test()
{
	ComplexNode* node1 = new ComplexNode(1);
	ComplexNode* node2 = new ComplexNode(3);
	ComplexNode* node3 = new ComplexNode(5);
	ComplexNode* node4 = new ComplexNode(7);
	ComplexNode* node5 = new ComplexNode(9);

	node1->_next = node2;
	node2->_next = node3;
	node3->_next = node4;
	node4->_next = node5;
	
	node1->_random = node3;
	node2->_random = node1;
	node3->_random = NULL;
	node4->_random = node2;
	node5->_random = node5;
	
	CopyComplexNode(node1);

}


int main()
{
	List l;
	l.Push(0);
	l.Push(1);
	l.Push(2);
	l.Push(3);
	l.Push(5);
	l.Push(7);
	l.Push(9);

	List l1;
	l1.Push(0);
	l1.Push(2);
	l1.Push(4);
	l1.Push(6);
	l1.Push(8);
	l1.Push(9);

	ListNode* tmp = l1.Find(8);
	ListNode* tmp2 = l.Tail();
	tmp2->_next = tmp;
	l.Push(10);
	l.Push(11);
	cout<<l.IsCross(&l1)<<endl;

	l.Print();
	l1.Print();

	List l2;
	l2.Push(1);
	l2.Push(2);
	l2.Push(3);
	l2.Push(4);
	l2.Push(5);
	 tmp = l2.Tail();
	 tmp2 = l2.Find(3);
	tmp->_next = tmp2;
	
	//tmp = l2.EntryLoop();
	//cout<<tmp->_data<<endl;
	//cout<<l2.IsLoop()<<endl;
	//cout<<l2.LoopLength()<<endl;
	//ListNode* tmp1 = l.Head();
	//ListNode* tmp2 = l1.Head();

	//l.UnionSet(tmp1,tmp2);
	//l.Print();
	//l.PrintTailToHead();
	//l.PrintTailToHeadR();
	//l.Reverse();
	//ListNode* tmp = l.Find(3);
	//if(tmp)
	//	l.PushNodeNonHead(tmp,0);
	//l.DeleteNonTail(tmp);
	//l.Print();
	//l.ListSort();
	//l.ListQuickSort();error
	//l.QuickSortList();
	//l.Print();
	//l1.Print();
	//ListNode* tmp = l.FindMidList();
	//cout<<tmp->_data<<endl;
	/*ListNode* tmp = l.LastKNode(9);
	
	if(tmp)
		cout<<tmp->_data<<endl;*/
	//l.Meragesort(&l1);
	//l1.Print();

	//Test();
	system("pause");
	return 0;
}



//#include<iostream>
//#include<assert.h>
//using namespace std;
//
//int PartSort(int *a,int begin,int end)
//{
//       int left = begin;
//       int right = end;
//       while (left < right)
//       {
//              while (left < right&&a[left]<=a[end])     //找到一个大于基准值的值
//              {
//                     left++;
//              }
//              while (left < right&&a[right] >=a[end])    //找到一个小于基准值的值
//              {
//                     right--;
//              }
//              if (left<right)
//                     swap(a[left],a[right]);
//       }
//       swap(a[left], a[end]);
//       return left;
//}
//
//void QuickSort(int *a,int begin,int end)
//{
//       assert(a);
//       int div=PartSort(a,begin,end);
//       if (div-1>begin)                 //这个区间的元素个数大于一个的时候就要在进行划分排序
//           QuickSort(a,begin,div-1);
//       if (div+1<end)
//              QuickSort(a,div+1,end);
//}
//
//int PartSort(int *a,int begin,int end)
//{
//       int left = begin;
//       int right = end;
//       int key = a[end];
//       int blank = end;
//       while (left<right)
//       {
//              if (blank == right)        //从左边开始找一个比基准数大的值
//              {
//                     while (left<right&&a[left]<=key)
//                     {
//                           left++;
//                     }
//                     a[blank] = a[left];
//                     blank = left;
//              }
//              else if (blank == left)    //从右边开始找一个比基准值小的值
//              {
//                     while (left<right&&a[right]>=key)
//                     {
//                           right--;
//                     }
//                     a[blank] = a[right];
//                     blank = right;
//              }
//       }
//       a[blank] = key;
//       return blank;
//}
//void QuickSort(int *a,int begin,int end)
//{
//       assert(a);
//       if (begin < end)
//       {
//              int div=PartSort(a,begin,end);
//              QuickSort(a,begin,div-1);
//              QuickSort(a,div+1,end);
//       }
//}
//
//
//int PartSort(int* a,int begin,int end)
//{
//       int prev = begin - 1;
//       int cur = begin;
//       while (cur<end)
//       {
//              if (a[cur] < a[end])
//              {
//                     prev++;
//                     if (prev != cur)
//                           swap(a[prev], a[cur]);
//              }
//              cur++;
//       }
//       prev++;
//       swap(a[prev], a[end]);
//       return prev;
//}
////利用前后指针来快速的实现划分左右子区间
//void QuickSort(int *a,int begin,int end)
//{
//       assert(a);
//       if (end>begin)
//       {
//              int div = PartSort(a, begin, end);
//              QuickSort(a, begin, div - 1);
//              QuickSort(a, div + 1, end);
//       }
//}
//int main()
//{
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int num = 0;
//	cin>>num;
//	int sum_e = 0;
//	int sum_o = 0;
//	int i,j,sum1,sum2;
//
//	if(num >= 1)
//	{
//		sum1 = 1;
//		sum_e = 1;
//	}
//	if(num >= 2)
//	{	
//		sum2 = 2;
//		sum_o = 2;
//	}
//
//	for(i=3,j=4; (i<=num)||(j<=num); i+=2,j+=2)
//	{
//		if(i<=num)
//		{
//			sum1 = sum1*i*(i-1);
//			sum_e += sum1;
//		}
//		if(j<=num)
//		{
//			sum2 = sum2*j*(j-1);
//			sum_o += sum2;
//		}
//	}
//	cout<<sum_e<<endl<<sum_o<<endl;
//	system("pause");
//	return 0;
//}
//
////
////#define LEN 128
////
////int main()
////{
////	int a = 0;
////	int i = 0;
////	int num[LEN];
////	memset(num, 0, LEN);
////	cin>>a;
////	while(a > 0)
////	{
////		num[i] = a%8;
////		a/=8;
////		i++;
////	}
////
////	for(int j=i-1; j>0; j--)
////	{
////		cout<<num[j];
////	}
////	cout<<endl;
////	system("pause");
////	return 0;
////}
////
////
////////#include "MuchFish.h"
////////#include "Circleword.h"
////////#include "二维数组中的查找.h"
//////#include<string.h>
//////int main()
//////{
//////	char* str = "We Are Happy";
//////	int len = strlen(str);
//////	//replaceSpace(str,len);
//////	int spaceNum=0;
//////	for(int i=0;i<len;i++)
//////	{
//////	  if(str[i]==' ')
//////		  spaceNum++;                
//////	}
//////	int newindex=len+2*spaceNum;
//////	char *index=str+len;
//////	while(index>=str)
//////	{
//////		if(*index==' ')
//////		{
//////			str[newindex--]='0';
//////			str[newindex--]='2';
//////			str[newindex--]='%';
//////		}
//////        else
//////		{
//////			str[newindex--]=*index;
//////		}
//////		index--;
//////	}
//////	cout<<str<<endl;
//////	system("pause");
//////	return 0;
//////}
////////#include<cstdio>
////////#include<cstdlib>
////////#include <iostream>
////////#include <string>
////////#include <algorithm>
////////#include <cstring>
////////#include <map>
////////#include <vector>
////////using namespace std;
////////#define MAX 50+5
////////#define MAXLEN 50+5
////////
////////int n;
////////string w[MAX];
////////vector<string> t;
////////int search(const string& str)
////////{
////////    for(int i=0;i<t.size();++i)
////////    {
////////        if (t[i].size() == str.size() * 2)
////////        {
////////            if (t[i].find(str) != -1)
////////                return 1;
////////        }
////////    }
////////    return 0;
////////}
////////int main()
////////{
////////    while(cin>>n)
////////    {
////////        t.clear();
////////        for (int i = 0; i < n; ++i)
////////            scanf("%s",&w[i]);
////////        for(int i=0;i<n;++i)
////////        {
////////            if(!search(w[i]))
////////            {
////////                //重复两遍，构建模式
////////                string pattern(w[i]);
////////                pattern.append(w[i]);
////////
////////                t.push_back(pattern);
////////            }
////////        }
////////        printf("%d\n", t.size());
////////    }
////////
////////    return 0;
////////}