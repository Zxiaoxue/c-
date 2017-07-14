/*************************************************************************
	> File Name: BTree.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 11 Jul 2017 06:36:16 PM PDT
 ************************************************************************/

#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
using namespace std;

struct BTreeNode
{
	int _value;
	BTreeNode* _left;
	BTreeNode* _right;

	BTreeNode(int value)
		:_value(value)
		 ,_left(NULL)
		 ,_right(NULL)
	{}

};

class BTree
{
	typedef BTreeNode Node;
	public:

	BTree()
		:_root(NULL)
	{}

	BTree(const BTree& bt)
	{
		_root = _Copy(bt._root);
	}

	BTree operator=(const BTree& bt)
	{
		if(this != &bt)
		{
			BTree tmp(bt);
			swap(_root, tmp._root);
		}
	}

	~BTree()
	{
		_Destory(_root);
	}

	void CreateBTree(int* a, int size, int invalid)
	{
		int index = 0;
		_root = _CreateBTree(a, size, index, invalid);
	}

	void PrevOrderR()
	{
		_PrevOrderR(_root);
		cout<<endl;
	}

	void InOrderR()
	{
		_InOrderR(_root);
		cout<<endl;
	}

	void PostOrderR()
	{
		_PostOrderR(_root);
		cout<<endl;
	}

	void LevelOrder()
	{
		queue<Node*> q;

		Node* cur = _root;
		q.push(cur);

		while( !q.empty() )
		{
			Node* tmp = q.front();
			cout<<tmp->_value<<" ";

			if(tmp->_left)
				q.push(tmp->_left);
			if(tmp->_right)
				q.push(tmp->_right);
			
			q.pop();
		}
		cout<<endl;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
	}
	
	void InOrder()
	{
		_InOrder(_root);
	}

	void PostOrder()
	{
		_PostOrder(_root);
	}

	int Heigh()
	{
		return _Heigh(_root);
	}

	int Size()
	{
		_Size(_root);
	}

	int Leaf()
	{
		_Leaf(_root);
	}

	private:
	
	int _Heigh(Node* root)
	{

		if(root == NULL)
			return 0;
			
		return _Heigh(root->_left) > _Heigh(root->_right) ? _Heigh(root->_left)+1:_Heigh(root->_right)+1;
	}

	int _Size(Node* root)
	{
		if(root == NULL)
			return 0;

		return 1+_Size(root->_left) + _Size(root->_right);
	}

	int _Leaf(Node* root)
	{
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}
		
		return _Leaf(root->_left)+_Leaf(root->_right);
	}

	Node* _CreateBTree(int* a, int size, int& index, int invalid)
	{
		assert(a);
		Node* root = NULL;

		if(index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateBTree(a, size, ++index, invalid);
			root->_right = _CreateBTree(a, size, ++index, invalid);
		}

		return root;
	}

	Node* _Copy(Node* root)
	{
		Node* newRoot = NULL;
		Node* cur = root;

		if(cur != NULL)
		{
			newRoot = new Node(cur->_value);
			newRoot->_left = _Copy(cur->_left);
			newRoot->_right = _Copy(cur->_right);
		}

		return newRoot;
	}

	void _Destory(Node* root)
	{
		Node* del = root;

		if(del)
		{
			_Destory(del->_left);
			_Destory(del->_right);
			delete del;
			del = NULL;
		}
	}

	void _PrevOrderR(Node* root)
	{
		if(root != NULL)
		{
			cout<<root->_value<<" ";
			_PrevOrderR(root->_left);
			_PrevOrderR(root->_right);
		}
	}

	void _InOrderR(Node* root)
	{
		if(root != NULL)
		{
			_InOrderR(root->_left);
			cout<<root->_value<<" ";
			_InOrderR(root->_right);
		}
	}

	void _PostOrderR(Node* root)
	{
		if(root != NULL)
		{
			_PostOrderR(root->_left);
			_PostOrderR(root->_right);
			cout<<root->_value<<" ";
		}
	}
	
	void _PrevOrder(Node* root)
	{
		assert(root);
		stack<Node*> s;
		s.push(root);
		int flag = 1;

		Node* cur = NULL;
		while(!s.empty())
		{
			cur = s.top();
			if(flag == 1)
			{
				if(cur->_left == NULL)
				{
					flag = 2;
				}
				else
				{
					cout<<cur->_value<<" ";
					s.push(cur->_left);
				}
			}
			else if(flag == 2)
			{
				if(cur->_right == NULL)
					flag = 3;
				else
				{
					s.push(cur->_right);
					flag = 1;
				}
			}
			else
			{
				Node* tmp = NULL;
				if(!s.empty())
				{
					tmp = s.top();
					s.pop();
				}

				cur = tmp;
				while(!s.empty() && s.top()->_right == tmp)
				{
					tmp = s.top();
					s.pop();
				}

				cout<<cur->_value<<" ";

				flag = 2;
			}
		}

		cout<<endl;
	}


	void _InOrder(Node* root)
	{
		assert(root);
		Node* cur = NULL;

		stack<Node*> s;
		s.push(root);
		int flag = 1;

		while(!s.empty())
		{
			cur = s.top();

			if(flag == 1)
			{
				if(cur->_left == NULL)
				{
					flag = 2;
				}
				else
				{
					s.push(cur->_left);
				}
			}
			else if(flag == 2)
			{
				if(cur->_right != NULL)
				{
					cout<<cur->_value<<" ";
					s.push(cur->_right);
					flag = 1;
				}
				else
					flag = 3;
			}
			else
			{
				Node* tmp = NULL;
				if(!s.empty())
				{
					tmp = s.top();
					s.pop();
				}

				cout<<tmp->_value<<" ";

				while(!s.empty() && s.top()->_right == tmp)
				{
					tmp = s.top();
					s.pop();
				}

				flag = 2;
			}

		}

		cout<<endl;
	}

	void _PostOrder(Node* root)
	{
		assert(root);

		Node* cur = NULL;
		stack<Node*> s;
		s.push(root);
		int flag = 1;

		while(!s.empty())
		{
			cur = s.top();
			if(flag == 1)
			{
				if(cur->_left == NULL)
					flag = 2;
				else
					s.push(cur->_left);
			}
			else if(flag == 2)
			{
				if(cur->_right == NULL)
					flag = 3;
				else
				{
					s.push(cur->_right);
					flag = 1;
				}
			}
			else
			{
				Node* tmp = NULL;
				if(!s.empty())
				{
					tmp = s.top();
					s.pop();
				}

				cout<<tmp->_value<<" ";
				
				while(!s.empty() && s.top()->_right == tmp)
				{
					tmp = s.top();
					s.pop();
					cout<<tmp->_value<<" ";
				}
				flag = 2;
			}
		}
		cout<<endl;
	}

	private:
	Node* _root;
};

void Test()
{
	int a[] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7};
	size_t size = sizeof(a)/sizeof(int);
	BTree bt;
	bt.CreateBTree(a, size, '#');

	cout<<bt.Leaf()<<endl;;

	cout<<bt.Size()<<endl;
	cout<<bt.Heigh()<<endl;
	//bt.LevelOrder();
	//bt.PrevOrder();
	//bt.InOrderR();
	//bt.InOrder();
	bt.PostOrderR();
	bt.PostOrder();

//	BTree bt2(bt);
//	bt.PrevOrderR();
//	bt2.PrevOrderR();
//	bt.InOrderR();
//	bt.PostOrderR();
}
#endif //_BTREE_H_
