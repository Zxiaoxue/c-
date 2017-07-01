#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <algorithm>
using namespace std;

struct Node
{
	int value;
	Node* pLeft;
	Node* pRight;
};
bool bInvalidInput = false;

Node* solvecore(int* startPre,int* endPre,int* startIn,int* endIn)
{
	if(bInvalidInput)
		return NULL;
	Node* root = new Node();
	int rootvalue = startPre[0];
	root->value = rootvalue;
	root->pLeft = root->pRight = NULL;
	if(startPre == endPre)
	{
		if( startIn == endIn && *startIn == *startPre)
			return root;
		else
		{
			bInvalidInput = true;
			return NULL;
		}
	}
	int* pIn = startIn;
	while(*pIn != rootvalue && pIn < endIn)
		++pIn;
	if(*pIn != rootvalue && pIn == endIn)
	{
		bInvalidInput = true;
		return NULL;
	}
	int leftLength = pIn - startIn;
	int* endP = startPre + leftLength;
	if(leftLength > 0)
	{
		root->pLeft = solvecore(startPre+1,endP,startIn,pIn-1);
		if(bInvalidInput)
			return NULL;
	}
	if(leftLength < endPre - startPre)
	{
		root->pRight = solvecore(endP+1,endPre,pIn+1,endIn);
		if(bInvalidInput)
			return NULL;
	}

	return root;

}
void postOrder(Node* root)
{
	if(root == NULL)
		return ;
	if(root->pLeft != NULL)
		postOrder(root->pLeft);
	if(root->pRight != NULL)
		postOrder(root->pRight);
	cout<<root->value<<" ";
}
void solve(int preOrder[],int midOrder[],int NodeNum)
{
	if(preOrder == NULL || midOrder == NULL || NodeNum <= 0)
	{
		cout<<"No"<<endl;
		return ;
	}
	bInvalidInput = false;
	Node* root = solvecore(preOrder,preOrder + NodeNum -1,midOrder,midOrder + NodeNum -1);
	
	if(root != NULL && !bInvalidInput)
	{
		postOrder(root);
		cout<<endl;
	}
	else
		cout<<"No"<<endl;
}

int main()
{
	//freopen("6.txt","r",stdin);
	const int Max_Num = 1005;
	int preOrder[Max_Num],midOrder[Max_Num];
	int NodeNum;
	while(cin>>NodeNum)
	{
		memset(preOrder,0,sizeof(preOrder));
		memset(midOrder,0,sizeof(midOrder));
		int i;
		for(i = 0;i < NodeNum ;i++)
			cin>>preOrder[i];
		for(i = 0;i < NodeNum ;i++)
			cin>>midOrder[i];
		solve(preOrder,midOrder,NodeNum);
		
	}
	return 0;
}