#include<iostream>
using namespace std;
#include<vector>
typedef struct ListNode
{
	int val;
	struct ListNode* next;
	ListNode(int x)
	{
		val = x;
		next = NULL;
	}
};

vector<int> printListFromTailToHead(ListNode* head)
{
	vector<int> v;
	ListNode* newTail = head;
	ListNode* cur = head;
	ListNode* next = head->next;

	while(next != NULL)
	{
		cur = newTail;
		cur = next;
		next = cur->next;
		v.push_back(newTail->val);
	}

}