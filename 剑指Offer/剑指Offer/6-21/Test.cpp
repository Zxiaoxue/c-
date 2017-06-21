/*************************************************************************
	> File Name: Test.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Wed 21 Jun 2017 04:13:23 AM PDT
 ************************************************************************/

#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct ListNode{
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {}
};

class Solution {
	public:
		vector<int> printListFromTailToHead(ListNode* head) {
			vector<int> v;
			if(head == NULL)
				return v;
			stack<int> s;
			s.push(head->val);
			ListNode* cur = head->next;
			while(cur != NULL){
				s.push(cur->val);
				cur = cur->next;
			}
			while(!s.empty()){
				int tmp = s.top();
				s.pop();
				v.push_back(tmp);
			}
			return v;
		}
};
