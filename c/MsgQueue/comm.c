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
		return -1;
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
	int ret = msgctl(msgid, IPC_RMID, 0);
	if(ret < 0)
	{
		perror("msgctl");
		return -1;
	}
	return ret;
}

int sendMsg(int msgid, int type, char* msg)
{
	struct msgbuf buf;
	buf.mtype = type;
	strcpy(buf.mtext, msg);
	int s = msgsnd(msgid, &buf, sizeof(buf.mtext), 0);
	if(s < 0)
	{
		perror("msgsnd");
	}
	return s;
}

int recvMsg(int msgid, int type, char out[])
{
	struct msgbuf buf;
	int s = msgrcv(msgid, &buf, sizeof(buf.mtext), type, 0);
	if(s > 0)
	{
		buf.mtext[s] = 0;
		strncpy(out, buf.mtext, s);
		return 0;
	}
	perror("msgrecv");
	return -1;
}











