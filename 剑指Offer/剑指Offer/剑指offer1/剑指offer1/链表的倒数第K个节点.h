#include <iostream>
#include <assert.h>
using namespace std;

struct ListNode
{
	int _data;
	ListNode* _next;
};

ListNode* FindKthToTail(ListNode* pHead, int k)
{
	assert(pHead);
	assert(k>0);
	int num = k;
	ListNode* fast = pHead;
	ListNode* slow = pHead;

	while(fast != NULL && num >= 0)
	{
		fast = fast->_next;
	}

	while(fast != NULL && fast->_next != NULL)
	{
		fast = fast->_next;
		slow = slow->_next;
	}

	return slow;
}