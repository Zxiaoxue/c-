/*************************************************************************
	> File Name: tserver.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 12 Mar 2017 06:38:21 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>

void* handle_fd(void* arg)
{
	int sock = *((int*)arg);
	char buf[1024];
	while(1)
	{
		ssize_t s = read(sock, buf, sizeof(buf)-1);

		if(s > 0)
		{
			buf[s-1] = 0;
			printf("client# %s\n",buf);
		}
		else
		{
			printf("client is quit!\n");
			break;
		}
	}
	close(sock);
}

int statup(int port, const char* ip)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(ip);
	local.sin_port = htons(port);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local))< 0)
	{
		perror("bind");
		return 2;
	}

	if(listen(sock, 5) < 0)
	{
		perror("listen");
		return 3;
	}

	return sock;
}

void Usage(char* proc)
{
	printf("usage: %s [local_ip] [local_port]",proc);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}
	int listen_sock = statup(atoi(argv[2]), argv[1]);

	struct sockaddr_in peer;
	int len = sizeof(peer);

	while(1)
	{
		int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
		if(sock < 0)
		{
			perror("accept");
			return 2;
		}

		pthread_t tid;
		int ret = pthread_create(&tid, NULL, handle_fd, &sock);
		if(ret != 0)
		{
			perror("pthread_create");
			return 3;
		}


		printf("get client ip:%s port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));

//		pthread_join(tid,NULL);
		pthread_detach(tid);
//		close(sock);
	}

	return 0;
}
