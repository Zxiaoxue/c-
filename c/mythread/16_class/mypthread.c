/*************************************************************************
	> File Name: mypthread.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Mon 20 Feb 2017 06:07:04 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
  
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
typedef struct node
{
	int _data;
	struct node* _next;
}node_t,*node_p,**node_pp;

node_p CreatNode(node_pp list, int data)
{
	assert(list);
//	if(list == NULL)
//	{
//		printf("list is NULL\n");
//		return NULL;
//	}

	node_p node = (node_p)malloc(sizeof(node_t));
	node->_next = NULL;
	node->_data = data;

	return node;
}
void InitList(node_pp list)
{
	assert(list);
	*list = CreatNode(list,0);
}


int IsEmpty(node_p list)
{
//	assert(list);
	if((list == NULL) || list->_next == NULL)
	{
	//	printf("list next is NULL\n");
		return 1;
	}
	else
		return 0;
}

void PushHead(node_p list, int data)
{
	assert(list);
//	if(list == NULL)
//	{
//		printf("list is NULL\n");
//		return;
//	}
	node_p node = CreatNode(&list,data);
	
	if(node != NULL)
	{
	//	printf("node is not NULL! data is %d\n",node->_data);
		node->_next = list->_next;
		list->_next = node;
	}
	
}

void DelNode(node_p node)
{
	node->_next = NULL;
	node->_data = 0;
	free(node);
}

void PopHead(node_p list)
{
	//assert(list);
	//if(list == NULL || list->_next == NULL)
	if(list == NULL)
	{
		return;
	}
	else
	{
		node_p del = list->_next;
		list->_next = del->_next;
	    DelNode(del);
	}
}

void DestoryList(node_p list)
{
	node_p del = list->_next;
	while(del)
	{
		PopHead(list);
		del = del->_next;
	}

	DelNode(list);
}


void Show(node_p list)
{
	assert(list);
	node_p node = list->_next;
	//int i = IsEmpty(list);
	//printf("IsEmpty: %d",i);
	while(node)
	{
		printf("%d ",node->_data);
		node = node->_next;
	}
	printf("\n");

}

void* thread_product(void* arg)
{
	node_p head = (node_p)arg;
	//InitList(&head);
	while(1)
	{
		usleep(1236);
		srand((unsigned int )time(NULL));
		int data = rand()%10000;
		pthread_mutex_lock(&mylock);
		PushHead(head,data);
		pthread_mutex_unlock(&mylock);
		pthread_cond_signal(&mycond);
		printf("product done,data is: %d\n",data);
	}
}

void *thread_consumer(void* arg)
{
	node_p head = (node_p)arg;
	while(1)
	{
	//	sleep(1);
		pthread_mutex_lock(&mylock);
		if( IsEmpty(head) )
		{
			pthread_cond_wait(&mycond, &mylock);
		}
		PopHead(head);
		pthread_mutex_unlock(&mylock);
		printf("consumer done.data is: %d\n",head->_data);
	}
}

int main()
{
	node_p head;
	InitList(&head);

	pthread_t tid1,tid2;
	int ret1 = pthread_create(&tid1,NULL,thread_product, head);
	int ret2 = pthread_create(&tid2,NULL,thread_consumer, head);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;

	//node_p list;
	//InitList(&list);
	//Show(list);
	//int i = 0;

	//for(; i<10; i++)
	//{
	//	PushHead(list,i);
	//	Show(list);
	//}

	//for(; i>5; i--)
	//{
	//	PopHead(list);
	//	Show(list);
	//}
	//DestoryList(list);
	//Show(list);
	//return 0;
}
