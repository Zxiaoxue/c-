/*************************************************************************
	> File Name: mysem.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 21 Feb 2017 04:08:20 AM PST
 ************************************************************************/

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define _SIZE_ 30

sem_t blanks;
sem_t datas;

int ringBuf[_SIZE_];

void *productRun(void *arg)
{
	int i = 0;
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		sem_wait(&blanks);
		int data = rand()%1234;
		ringBuf[i++] = data;
		i %= _SIZE_;
		printf("product is done... data is: %d\n",data);
		sem_post(&datas);
		//pthread_mutex_unlock(&mutex);
	}
}
void *productRun2(void *arg)
{
	int i = 0;
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		sem_wait(&blanks);
		int data = rand()%1234;
		ringBuf[i++] = data;
		i %= _SIZE_;
		printf("product2 is done... data is: %d\n",data);
		sem_post(&datas);
		//pthread_mutex_unlock(&mutex);
	}
}

void *consumerRun(void *arg)
{
	int i = 0;
	while(1)
	{
		usleep(1456);
		pthread_mutex_lock(&mutex);
		sem_wait(&datas);
		int data = ringBuf[i++];
		i %= _SIZE_;
		printf("consumer is done... data is: %d\n",data);
		sem_post(&blanks);
		pthread_mutex_unlock(&mutex);
	}
}

void *consumerRun2(void *arg)
{
	int i = 0;
	while(1)
	{
		usleep(1234);
		pthread_mutex_lock(&mutex);
		sem_wait(&datas);
		int data = ringBuf[i++];
		i %= _SIZE_;
		printf("consumer2 is done...data2 is: %d\n",data);
		sem_post(&blanks);
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	sem_init(&blanks, 0, _SIZE_);
	sem_init(&datas, 0, 0);

	pthread_t tid1,tid2,tid3,tid4;
	pthread_create(&tid1, NULL, productRun, NULL);
	pthread_create(&tid4, NULL, productRun2, NULL);
	pthread_create(&tid2, NULL, consumerRun, NULL);
	pthread_create(&tid3, NULL, consumerRun2, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);

	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;
}
