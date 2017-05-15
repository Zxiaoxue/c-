/*************************************************************************
	> File Name: client.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 14 May 2017 07:19:07 AM PDT
 ************************************************************************/

#include<stdio.h>
#include "comm.h"
int main()
{
	int msgid = getMsgQueue();
	//printf("getMsgQueu:%d\n", msgid);
	if(msgid < 0)
	{
		return 1;
	}
	char buf[1024];
	while(1)
	{
		if(recvMsg(msgid, SERVER_TYPE, buf) < 0)
		{
			break;
		}
		printf("recv from server:%s\n", buf);
		printf("Please Enter:\n");
		int s = read(0, buf, sizeof(buf));
		if(s > 0)
		{
			buf[s] = '\0';
			sendMsg(msgid, CLIENT_TYPE, buf);
		}
	}
	return 0;
}
