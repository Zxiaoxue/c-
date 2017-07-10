#include <iostream>
#include <assert.h>
#include<stack>
using namespace std;

struct ListNode
{
	int _data;
	ListNode* _next;
	ListNode(const int& data = 0)
		:_data(data)
		,_next(NULL)
	{}
};

class List
{
	typedef ListNode Node;
public:

	List()
		:_head(NULL)
	{}

	void Push(int data)
	{
		Node* tmp = new Node(data);

		if(_head == NULL)
			_head = tmp;
		else
		{
			Node* cur = _head;
			while(cur != NULL && cur->_next != NULL)
			{
				cur = cur->_next;
			}
			cur->_next = tmp;
		}
	}

	void Print()
	{
		if(_head == NULL)
			return;
		Node* cur = _head;

		while(cur)
		{
			cout<<cur->_data<<" ";
			cur = cur->_next;
		}
		cout<<endl;
	}
	//�����������
	Node* Reverse()
	{
		if(_head == NULL)
			return NULL;
		Node* cur = _head;
		Node* newHead = NULL;
		Node* next = cur->_next;

		/*while(next != NULL)
		{
			cur->_next = newHead;
			newHead = cur;
			cur = next;
			next = cur->_next;
		}
		cur->_next = newHead;
		newHead = cur;*/
		while(cur != NULL)
		{
			cur->_next = newHead;
			newHead = cur;
			cur = next;
			if(cur != NULL)
			{
				next = cur->_next;
			}
		}
		return newHead;
	}


	//��β��ͷ��ӡ������---����stack

	void PrintTailToHead()
	{
		if(_head == NULL)
			return;
		stack<Node*> s;
		Node* cur = _head;
		while(cur)
		{
			s.push(cur);
			cur = cur->_next;
		}

		while(!s.empty())
		{
			cout<<s.top()->_data<<" ";
			s.pop();
		}
		cout<<endl;
	}
	//�ݹ�д��
	void PrintTailToHeadR()
	{
		_PrintTailToHeadR(_head);
		cout<<endl;
	}

	void _PrintTailToHeadR(Node* node)
	{
		if(node == NULL)
			return;
		_PrintTailToHeadR(node->_next);
		cout<<node->_data<<" ";
	}

	//ɾ��һ����ͷ������ķ�β�ڵ�
	void DeleteNonTail(Node* pos)
	{
		assert(pos && pos->_next);

		Node* cur = pos;
		Node* del = cur->_next;
		Node* next = del->_next;

		cur->_data = del->_data;
		cur->_next = next;
		delete del;
		del = NULL;
	}

	Node* Find(int data)
	{
		if(_head == NULL)
			return NULL;
		Node* cur = _head;
		while(cur != NULL)
		{
			if(cur->_data == data)
				return cur;
			cur = cur->_next;
		}
	}


	//����ͷ�������һ����ͷ�ڵ�ǰ����һ���ڵ�
	void PushNodeNonHead(Node* pos, int data)
	{
		assert(pos);
		Node* tmp = new Node(data);
		Node* cur = pos;
		Node* next = pos->_next;
		
		//�ѽڵ㴮������
		tmp->_next = next;
		cur->_next = tmp;
		

		tmp->_data = cur->_data;
		cur->_data = data;
	}

	//������ʵ��Լɪ��
	//7.����������ð������&��������
	void ListSort()//Bubble
	{
		if(_head == NULL)
			return;
		Node* cur = _head;
		Node* next = NULL;
		Node* tail = NULL;

		while(_head != tail)
		{
			int flag = 0;
			cur = _head;
			next = cur->_next;
			while(next != tail)
			{
				if(cur->_data > next->_data)
				{
					int tmp = cur->_data;
					cur->_data = next->_data;
					next->_data = tmp;
					flag = 1;
				}
				cur = next;
				next = next->_next;
			}
			tail = cur;
			if(flag == 0)
				return;
		}
	}
	Node* Tail()
	{
		Node* tail = _head;
		while(tail->_next!= NULL)
		{
			tail = tail->_next;
		}
		return tail;
	}

	//QuickSort
	void ListQuickSort()
	{
		Node* tail = Tail();
		 _ListQuickSort(_head,tail);
	}
	Node* Div(Node* head,Node* tail)
	{
		Node* left = NULL;
		Node* leftHead = NULL;
		Node* right = NULL;
		Node* rightHead = NULL;
		Node* cur = head->_next;
		Node* div = head;

		while(cur != NULL)
		{
			if(cur->_data < div->_data)
			{
				if(left)
				{
					left->_next = cur;
					left = cur;
				}
				else
				{
					left = cur;
					leftHead = cur;
				}
			}
			else
			{
				if(right)
				{
					right->_next = cur;
					right = cur;
				}
				else
				{
					right = cur;
					rightHead = cur;
				}
			}
			cur = cur->_next;
		}

		div->_next = NULL;
 		if(leftHead)
		{
			head = leftHead;
			left->_next = div;	
		}
		else
			head = div;

		if(leftHead && rightHead == NULL)
		{
			return div;
		}
		if(rightHead)
		{
			div->_next = rightHead;
			left->_next = div;
 
		}
	
		return div;
	}


	void _ListQuickSort(Node* head,Node* tail)
	{
		
		if(!head || !tail || head->_next == tail \
			|| !head->_next->_next || head->_next->_next == tail)
			return;
		Node* div = Div(head,tail);

		_ListQuickSort(head,div);
		_ListQuickSort(div,tail);
	}

	//8.�ϲ�������������,�ϲ�����Ȼ����
	void Meragesort(List l)
	{}
//9.���ҵ�������м�ڵ㣬Ҫ��ֻ�ܱ���һ������
//10.���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������
//11.�жϵ������Ƿ���������������󻷵ĳ��ȣ��󻷵���ڵ㣿������ÿ���㷨��ʱ�临�Ӷ�&�ռ临�Ӷȡ�
//12.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣����������������
//13.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣������������ܴ������������桿
//14.��������ĸ��ơ�һ�������ÿ���ڵ㣬��һ��ָ��nextָ��ָ����һ���ڵ㣬����һ��randomָ��ָ����������е�һ������ڵ����NULL������Ҫ��ʵ�ָ�������������ظ��ƺ��������
//15.��������������������ͬ�����ݡ�void UnionSet(Node* l1, Node* l2);

private:
	Node* _head;
};