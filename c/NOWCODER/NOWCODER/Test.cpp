#include <iostream>
using namespace std;
//#include "MuchFish.h"
//#include "Circleword.h"
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}
#include<cstdio>
#include<cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
#define MAX 50+5
#define MAXLEN 50+5

int n;
string w[MAX];
vector<string> t;
int search(const string& str)
{
    for(int i=0;i<t.size();++i)
    {
        if (t[i].size() == str.size() * 2)
        {
            if (t[i].find(str) != -1)
                return 1;
        }
    }
    return 0;
}
int main()
{
    while(cin>>n)
    {
        t.clear();
        for (int i = 0; i < n; ++i)
            scanf("%s",&w[i]);
        for(int i=0;i<n;++i)
        {
            if(!search(w[i]))
            {
                //重复两遍，构建模式
                string pattern(w[i]);
                pattern.append(w[i]);

                t.push_back(pattern);
            }
        }
        printf("%d\n", t.size());
    }

    return 0;
}