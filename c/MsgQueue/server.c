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
	char buf[1024];
	while(1)
	{
		buf[0] = 0;
		recvMsg(msgid, SERVER_TYPE, buf);
		printf("recv from client#:%s\n", buf);

		printf("Please Enter:\n");
		fflush(stdout);
		int s = read(0, buf, sizeof(buf)-1);
		if(s > 0)
		{
			buf[s-1] = 0;
			printf("read from stdout buf:%s\n", buf);
			if(sendMsg(msgid, CLIENT_TYPE, buf) < 0)
			{
				return -1;
			}
			printf("send done,wait recv...\n");
		}
	}
	//sleep(6);
	destoryQueue(msgid);

	return 0;
}
