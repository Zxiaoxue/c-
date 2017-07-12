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
typedef struct ComplexNode
{
	int _data;
	ComplexNode* _next;
	ComplexNode* _random;

	ComplexNode(const int& data)
		:_data(data)
		,_next(NULL)
		,_random(NULL)
	{}
}ComplexNode;

//14.复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，
	//还有一个random指针指向这个链表中的一个随机节点或者NULL，现在要求实现复制这个链表，返回复制后的新链表。
	
	
	ComplexNode* CopyComplexNode(ComplexNode* head)
	{
		if(head == NULL)
			return NULL;

		//拷贝节点
		ComplexNode* cur = head;
		while(cur)
		{
			ComplexNode* next = cur->_next;
			ComplexNode* tmp = new ComplexNode(cur->_data);
			cur->_next = tmp;
			tmp->_next = next;

			cur = next;
		}

		//置random指针
		cur = head;

		while(cur)
		{
			ComplexNode* next = cur->_next;
			if(cur->_random)
				next->_random = cur->_random->_next;

			cur = cur->_next->_next;
		}	
		//拆分源节点

		ComplexNode* newHead = head->_next;
		ComplexNode* newTail = newHead;
		cur = head;

		while(cur)
		{
			ComplexNode* next = cur->_next;
			cur->_next = next->_next;

			newTail->_next = next;
			newTail = next;

			cur = cur->_next;
		}

		return newHead;
	}


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
	void QuickSortList()
	{
		_QuickSortList(_head,NULL);
	}

	void _QuickSortList(Node* head,Node* tail)
	{
		if(head == NULL || head == tail || head->_next == tail)//链表空间为NULL或链表只有一个节点
			return;

		Node* prev = head;
		Node* cur = head->_next;
		int key = head->_data;

		while(cur != tail)
		{
			if(cur->_data < key)
			{
				prev = prev->_next;
				if(cur != prev)
				{
					int data = cur->_data;
					cur->_data = prev->_data;
					prev->_data = data;
				}
			}
			cur = cur->_next;
		}

		int data = prev->_data;
		prev->_data = head->_data;
		head->_data = data;

		_QuickSortList(head,prev);
		_QuickSortList(prev->_next,tail);
	}

	/*void ListQuickSort()
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
	}*/

	//8.合并两个有序链表,合并后依然有序
	List* Meragesort(List* l)
	{
		if(_head == NULL)
			return l;
		if(l->_head == NULL)
			return (List*)_head;

		Node* head1 = l->_head;
		Node* head2 = _head;

		if(head1->_data < head2->_data)
		{	
			_head = head1;
			head1 = head1->_next;
		}
		else
		{
			_head = head2;
			head2 = head2->_next;
		}

		Node* newTail = _head;
		while(head1 && head2)
		{
			if(head1->_data < head2->_data)
			{	
				newTail->_next = head1;
				head1 = head1->_next;
			}
			else
			{
				newTail->_next = head2;
				head2 = head2->_next;
			}
			newTail = newTail->_next;
		}

		if(head1)
			newTail->_next = head1;

		if(head2)
			newTail->_next = head2;

		return (List*)_head;
	}
	//9.查找单链表的中间节点，要求只能遍历一次链表
	Node* FindMidList()
	{
		if(_head == NULL)
			return NULL;
		Node* fast = _head;
		Node* slow = _head;

		while(fast && fast->_next)
		{
			slow = slow->_next;
			fast = fast->_next->_next;
		}
		return slow;
	}
	//10.查找单链表的倒数第k个节点，要求只能遍历一次链表
	Node* LastKNode(int k)
	{
		if(_head == NULL || k<=0)
			return NULL;
		
		int num = k;
		Node* fast = _head;
		Node* slow = _head;
		while(num-- && fast)
			fast = fast->_next;
		if(num > 0 || fast == NULL)
		{
			return NULL;
		}

		while(fast)
		{
			fast = fast->_next;
			slow = slow->_next;
		}
		return slow;
	}
	//11.判断单链表是否带环？若带环，求环的长度？求环的入口点？
	//并计算每个算法的时间复杂度&空间复杂度。
	//是否带环
	bool IsLoop()
	{
		bool flag = false;
		if(_head == NULL)
			return false;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				flag = true;
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		return flag;
	
	}
	//环的长度
	int LoopLength()
	{
		if(_head == NULL)
			return false;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		int length = 0;
		while(slow && fast && fast->_next)
		{
			length++;
			slow = slow->_next;
			fast = fast->_next->_next;

			if(slow == fast)
				break;
		}
		return length;
	}

	//环的入口点
	Node* EntryLoop()
	{
		if(_head == NULL || _head->_next == NULL)
			return NULL;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		if(fast == NULL || fast->_next == NULL)
			return NULL;

	

		return slow;
	}


	//12.判断两个链表是否相交，若相交，求交点。（假设链表不带环）
	bool IsCross(List* l)
	{
		if(_head == NULL || l->_head == NULL)
			return NULL;

		Node* tmp1 = _head;
		Node* tmp2 = l->_head;
		
		while(tmp1->_next)
		{
			tmp1 = tmp1->_next;
		}

		while(tmp2->_next)
		{
			tmp2 = tmp2->_next;
		}
		
		if(tmp1 == tmp2)
			return true;

		return false;
	}
	//13.判断两个链表是否相交，若相交，求交点。（假设链表可能带环）【升级版】
	//1.不相交，一个带环一个不带环
	//2.不相交，两个都带环
	//3.相交，两个都带环，相交不在环上
	//4.相交，两个都带环，相交在环上
	

	Node* Head()
	{
		return _head;	
	}

	//15.求两个已排序单链表中相同的数据。
	void UnionSet(Node* l1, Node* l2)
	{
		if(l1 == NULL || l2 == NULL)
			return;

		Node* tmp1 = l1;
		Node* tmp2 = l2;

		while(tmp1 && tmp2)
		{
			if(tmp1->_data == tmp2->_data)
			{
				cout<<tmp1->_data<<" ";
				tmp1 = tmp1->_next;
				tmp2 = tmp2->_next;
			}
			else if(tmp1->_data < tmp2->_data)
				tmp1 = tmp1->_next;
			else
				tmp2 = tmp2->_next;
		}
		cout<<endl;
	}


private:
	Node* _head;
};