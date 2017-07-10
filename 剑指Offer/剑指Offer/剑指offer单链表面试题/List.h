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
	//单链表的逆置
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


	//从尾到头打印单链表---借助stack

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
	//递归写法
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

	//删除一个无头单链表的非尾节点
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


	//在无头单链表的一个非头节点前插入一个节点
	void PushNodeNonHead(Node* pos, int data)
	{
		assert(pos);
		Node* tmp = new Node(data);
		Node* cur = pos;
		Node* next = pos->_next;
		
		//把节点串进链表
		tmp->_next = next;
		cur->_next = tmp;
		

		tmp->_data = cur->_data;
		cur->_data = data;
	}

	//单链表实现约瑟夫环
	//7.单链表排序（冒泡排序&快速排序）
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

	//8.合并两个有序链表,合并后依然有序
	void Meragesort(List l)
	{}
//9.查找单链表的中间节点，要求只能遍历一次链表
//10.查找单链表的倒数第k个节点，要求只能遍历一次链表
//11.判断单链表是否带环？若带环，求环的长度？求环的入口点？并计算每个算法的时间复杂度&空间复杂度。
//12.判断两个链表是否相交，若相交，求交点。（假设链表不带环）
//13.判断两个链表是否相交，若相交，求交点。（假设链表可能带环）【升级版】
//14.复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，还有一个random指针指向这个链表中的一个随机节点或者NULL，现在要求实现复制这个链表，返回复制后的新链表。
//15.求两个已排序单链表中相同的数据。void UnionSet(Node* l1, Node* l2);

private:
	Node* _head;
};