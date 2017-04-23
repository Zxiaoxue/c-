/*************************************************************************
	> File Name: pool_data.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 23 Apr 2017 07:17:37 AM PDT
 ************************************************************************/
#ifndef _POOL_DATA_H_
#define _POOL_DATA_H_
#include<iostream>
#include<semaphore.h>

using namespace std;

class pool_data
{
	public:
		pool_data();
		~pool_data();
		void putData(std::string& instring);
		void getData(std::string& outstring);
	private:
		pool_data(const pool_data&);
	private:
		int _cap;
		int _size;
		sem _blank;
		sem _data;
		vector<std::string> pool;

};

#endif
