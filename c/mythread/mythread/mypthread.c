/*************************************************************************
	> File Name: mypthread.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Feb 2017 08:12:40 AM PST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* thread_run(void *arg)
{
	int count = 5;
	while(count--)
	{
		sleep(1);
		printf("new thread pid: %d ppid: %d tid: %lu\n",getpid(),getppid(),pthread_self());
	}
	printf("new thread is over\n");
	return (void *)34;
}

int main()
{
	pthread_t tid;  
	int ret = pthread_create(&tid, NULL, thread_run, NULL);
	if(ret < 0)
	{
		perror("pthread_create");
		return -1;
	}

	//while(1)
	//{
	//	sleep(1);
	//	printf("main thread pid: %d ppid: %d tid: %lu\n",getpid(),getppid(),pthread_self());
	//}
		printf("main thread pid: %d ppid: %d tid: %lu\n",getpid(),getppid(),pthread_self());
	int exitcode = 0;
	pthread_join(tid,(void *)(&exitcode));
	printf("wait new thread is done...%d\n",exitcode);
	return 0;

}
