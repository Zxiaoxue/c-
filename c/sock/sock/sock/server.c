/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Wed 08 Mar 2017 01:20:17 AM PST
 ************************************************************************/

#include<stdio.h>

void startup()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		perror(socket);
		exit(1);
	}

}

int main()
{
	return 0;
}
