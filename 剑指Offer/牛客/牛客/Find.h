#include<iostream>
using namespace std;
#include<vector>

bool Find(int target, vector<vector<int> > array)
{
	int len = array.size()-1;
	int i = 0;

	while(len>=0&&i<=array[len].size())
	{
		if(array[len][i] < target)
		{
			++i;
		}
		else if(array[len][i] > target)
		{
			--len;
		}
		else
			return true;
	}

	return false;
}