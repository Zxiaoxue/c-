/*************************************************************************
	> File Name: data_pool.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 23 Apr 2017 07:16:41 AM PDT
 ************************************************************************/
#include "pool_data.h"
#include <iostream>
using namespace std;

pool_data::pool_data()
	:_cap(SIZE)
	,_size(0)
{
	sem_init(&_blank, SIZE, 0);
	sem_init(&_data, 0, 0);
}

void pool_data::putData(std::string& instring)
{
	int index = _size;
	sem_wait(&_blank);

	pool[index] = instring;
	_size++;
	_size %= _cap;

	sem_post(&_data);
}

void pool_data::gatData(std::string& outstring)
{
	int index = _size;
	sem_wait(&_data);
	
	outstring = pool[index];
	_size++;
	_size %= _cap;

	sem_post(&_blank);
}

pool_data::~pool_data()
{

}

