/*************************************************************************
	> File Name: comm.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Feb 2017 12:51:04 AM PST
 ************************************************************************/

#ifndef _COMM_
#define _COMM_
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#define PATHNAME "."
#define PROJID 0X6666
#define SIZE 4096*1
//struct shmid_ds 
//{
//	struct ipc_perm shm_perm;    /* Ownership and permissions */
//	size_t          shm_segsz;   /* Size of segment (bytes) */
//	time_t          shm_atime;   /* Last attach time */
//	time_t          shm_dtime;   /* Last detach time */
//	time_t          shm_ctime;   /* Last change time */
//	pid_t           shm_cpid;    /* PID of creator */
//	pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
//	shmatt_t        shm_nattch;  /* No. of current attaches */
//	...
//};

int creatShm();
int getShm();
int destoryShm(int shmid);
int atShm(int shmid, const void *arg, int flag);
int dtShm(const void *arg);

#endif //_COMM_
