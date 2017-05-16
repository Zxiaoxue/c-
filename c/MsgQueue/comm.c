/*************************************************************************
	> File Name: comm.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 14 May 2017 07:20:00 AM PDT
 ************************************************************************/

#include <stdio.h>
#include "comm.h"
int commMsgQueue(int flag)
{
	key_t _key = ftok(PROCPATH, PROCID);
	if(_key < 0)
	{
		perror("ftok");
		return -1;
	}
	int msgid = msgget(_key, flag);
	if(msgid < 0)
	{
		perror("msgget");
		return -2;
	}

	return msgid;
}

int creatMsgQueue()
{
	return commMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}

int getMsgQueue()
{
	return commMsgQueue(IPC_CREAT);
}

int destoryQueue(int msgid)
{
	if(msgctl(msgid, IPC_RMID, NULL) < 0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}

int sendMsg(int msgid, int type,const char* msg)
{
	struct msgbuf buf;
	buf.mtype = type;
	strcpy(buf.mtext, msg);

	int s = msgsnd(msgid, &buf, sizeof(buf.mtext), 0);
	if(s < 0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}

int recvMsg(int msgid, int type, char out[])
{
	struct msgbuf buf;
	printf("begin recvMsg!\n");
	if(msgrcv(msgid, (void*)&buf, sizeof(buf.mtext), type, 0) < 0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out, buf.mtext);
	printf("out: %s\n", buf.mtext);
	return 0;
}

