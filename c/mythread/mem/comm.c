/*************************************************************************
	> File Name: comm.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Feb 2017 12:51:04 AM PST
 ************************************************************************/

#include"comm.h"
static int commShm(int flag)
{
	key_t _k = ftok(PATHNAME,PROJID);
	if(_k < 0)
	{
		perror("ftok");
		return -1;
	}
	int shmid = shmget(_k, SIZE, flag);

	if(shmid < 0)
	{
		perror("shmget");
		return -2;
	}
	return shmid;
}

int creatShm()
{
	return commShm(IPC_CREAT|IPC_EXCL|0666);
}

int getShm()
{
	return commShm(IPC_CREAT);
}

int destoryShm(int shmid)
{
	
	if(shmctl(shmid, IPC_RMID, NULL))
	{
		perror("shmctl");
		return -1;
	}
	return 0;

}
int atShm(int shmid,const void *arg,int flag)
{
	if(shmat(shmid, arg, flag) < 0)
	{
		perror("shmat");
		return -1;
	}
	return 0;
}

int dtShm(const void* arg)
{
	if(shmdt(arg) < 0)
	{
		perror("shmdt");
		return -1;
	}
	return 0;
}

