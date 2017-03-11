/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 10 Mar 2017 09:26:04 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main(int argc, char* argv[])
{
	//printf("I am server!\n");
	if( argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]",argv[0]);
		return 1;
	}

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}
	//printf("sock = %d\n",sock);
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(argv[1]);
	local.sin_port = htons(atoi(argv[2]));

	//bind
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		return 3;
	}

	char buf[1024];
	int buflen = sizeof(buf);
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);

	while(1)
	{
		ssize_t s = recvfrom(sock, buf, buflen, 0, (struct sockaddr*)&peer, &len);

		if(s < 0)
		{
			perror("recvfrom");
			return 4;
		}
		else if(s == 0)
		{
			printf("client is quit!\n");
		}
		else
		{
			printf("client# %s\n",buf);
		}
	}

	close(sock);
	return 0;
}
