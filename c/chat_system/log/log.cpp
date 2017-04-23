/*************************************************************************
	> File Name: log.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 23 Apr 2017 07:09:01 AM PDT
 ************************************************************************/

#include<iostream>
#include "log.h"
using namespace std;

static std::string _level[] = {
		"[NORMAL]",
		"[NOTICE]",
		"[WARING]",
		"[FATAL]",
}


void printf_log(const char* msg, int level)
{
#ifdef DEBUG
	if(level >= 0 && level <= 3)
	{
		std::cout<<_level[level]<<msg<<std::endl;
	}
#endif
}

