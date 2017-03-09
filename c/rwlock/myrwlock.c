/*************************************************************************
	> File Name: myrwlock.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 21 Feb 2017 03:20:43 AM PST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int g_val = 0;
#define _SIZE_ 64

pthread_rwlock_t myrw;

void *readerRun(void* arg)
{
	while(1)
	{
		sleep(1);
		int ret = pthread_rwlock_rdlock(&myrw);
		if(ret == 0)
		{
			printf("reader is done..%d %s %d\n",ret,strerror(ret),g_val);
			pthread_rwlock_unlock(&myrw);
		}
	}
}

void *writerRun(void* arg)
{
	while(1)
	{
		sleep(1);
		int ret = pthread_rwlock_wrlock(&myrw);
		if(ret == 0)
		{
			g_val++;
			printf("writer is done..%d  %s\n",ret,strerror(ret));
			pthread_rwlock_unlock(&myrw);
		}
	}
}

int main()
{
	pthread_t tid1,tid2;

	pthread_rwlock_init(&myrw,NULL);

	pthread_create(&tid1, NULL, readerRun, NULL);
	pthread_create(&tid2, NULL, writerRun, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_rwlock_destroy(&myrw);
	return 0;
}
