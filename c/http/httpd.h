/*************************************************************************
	> File Name: httpd.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 01 Apr 2017 11:53:56 PM PDT
 ************************************************************************/
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
enum OP
{
	NORMAL,
	WARING,
	FATAL,
};

#define SIZE 4096

void usage(const char* proc);
int startup(const char* _ip, int _port);
void* accept_request(void *arg);
void printf_log(const char* msg, int i);
int handle_pthread(int sock);
int get_line(int sock, char* buf, size_t len);
