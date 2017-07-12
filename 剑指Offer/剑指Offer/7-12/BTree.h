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

	private:
	
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
	private:
	Node* _root;
};

void Test()
{
	int a[] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7};
	size_t size = sizeof(a)/sizeof(int);
	BTree bt;
	bt.CreateBTree(a, size, '#');
	bt.LevelOrder();
//	BTree bt2(bt);
//	bt.PrevOrderR();
//	bt2.PrevOrderR();
//	bt.InOrderR();
//	bt.PostOrderR();
}
#endif //_BTREE_H_
