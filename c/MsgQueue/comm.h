/*************************************************************************
> File Name: comm.h
> Author: ZX
> Mail: 18829897183@163.com 
> Created Time: Sun 14 May 2017 07:20:05 AM PDT
 ************************************************************************/

#ifndef _COMM_H_
#define _COMM_H_
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PROCPATH "."
#define PROCID 0X6666
#define SERVER_TYPE 1
#define CLIENT_TYPE 2


struct msgbuf
{               
	long mtype;/* message type, must be > 0 */
	char mtext[1];    /* message data */
};

int commMsgQueue(int flag);
int creatMsgQueue();
int getMsgQueue();
int destoryQueue(int msgid);
int sendMsg(int msgid, int type, char* msg);
int recvMsg(int msgid, int type, char out[]);

#endif //_COMM_H_
