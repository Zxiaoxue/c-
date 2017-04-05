/*************************************************************************
	> File Name: main.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 01 Apr 2017 11:54:03 PM PDT
 ************************************************************************/

#include"httpd.h"
#include<stdio.h>

void usage(const char* proc)
{
	printf("Usage:%s [local_ip][local_port]\n", proc);
}

void* accept_request(void *arg)
{
	//printf("accept_request!\n");
	int sock = (int)arg;
	pthread_detach(pthread_self());
	return (void*)handle_pthread(sock);
}

int main(int argc, const char* argv[])
{
	int ret = 0;
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	while(1)
	{
		int sock = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(sock < 0)
		{
			printf_log("accept failed!", 1);
			continue;
		}
		pthread_t tid;
		printf("get a connection ip:%s port:%d\n", inet_ntoa(client.sin_addr), htons(client.sin_port));
    	//		printf("before pthread_create!\n");
    	
		ret = pthread_create(&tid, NULL, accept_request, (void*)sock);
		if(ret < 0)
		{
			printf_log("pthread_creaite is failed!",WARING);
			close(sock);
    	}

	}

	return 0;
}
