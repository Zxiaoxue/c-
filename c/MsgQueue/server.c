/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 14 May 2017 07:18:59 AM PDT
 ************************************************************************/

#include <stdio.h>
#include "comm.h"
int main()
{
	int msgid  = creatMsgQueue();
	printf("createMsgQueue:%d\n", msgid);
	if(msgid < 0)
	{
		return 1;
	}
	while(1)
	{
		printf("Please Enter:\n");
		char buf[1024];
		int s = read(0, buf, sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			sendMsg(msgid, CLIENT_TYPE, buf);
		{
			break;
		}
		if(recvMsg(msgid, SERVER_TYPE, buf) < 0)
		{
			break;
		}
		printf("recv from client:%s\n", buf);
	
		}
	}
	//sleep(6);
	destoryQueue(msgid);

	return 0;
}
