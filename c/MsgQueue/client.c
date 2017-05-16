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
		buf[0] = 0;
		printf("Please Enter#:\n");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf));
		if(s > 0)
		{
			buf[s-1] = '\0';
			sendMsg(msgid, SERVER_TYPE, buf);
			printf("send done,wait recv...\n");
		}
		recvMsg(msgid, SERVER_TYPE, buf);
		printf("recv from server# %s\n", buf);
	}
	
	return 0;
}
