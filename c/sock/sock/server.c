/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 07 Mar 2017 10:46:18 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>

int startup(int _port, char* _ip)
{
	//creat socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);


	//bind socket
	if( bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0 )
	{
		perror("bind");
		exit(2);
	}

	//listen socket
	if( listen(sock, 5) < 0 )
	{
		perror("listen");
		exit(3);
	}
	
	printf("listen socket!\n");
	return sock;

}


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]\n",argv[0]);
		return 1;
	}
	int listen_sock = startup(atoi(argv[2]), argv[1]);
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);


	int id = fork();

	while(1)
	{
		if(id < 0)
		{
			perror("fork");
			exit(0);
		}
		else if(id == 0)
		{//child

			int sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
			if( sock < 0)
			{
				perror("accept");
				continue;
			}
			printf("after accept!\n");

			printf("get a client, ip: %s port; %d\n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));

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
		else
		{
			waitpid(id, NULL, WNOHANG);
		}
	}
//	printf("I am server!\n");
	return 0;
}
