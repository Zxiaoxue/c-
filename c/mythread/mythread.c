/*************************************************************************
	> File Name: mythread.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 18 Feb 2017 03:18:30 AM PST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
int count = 0;

void* thread_run(void *arg)
{
	while(1)
	{
		printf("new pthread...\n");
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_run, NULL);
	if(ret < 0)
	{
		perror("pthread_create");
		return 1;
	}

	pthread_join(tid);
	return 0;
}
