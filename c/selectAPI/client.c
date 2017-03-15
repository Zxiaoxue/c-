/*************************************************************************
	> File Name: client.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 07 Mar 2017 10:46:28 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
static void usage(char* porc)
{
	printf("Usage: %s [ip] [port]\n",porc);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		perror("sock");
		return 2;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));
	socklen_t len = sizeof(server);

	if(connect(sock, (struct sockaddr*)&server, len) < 0)
	{
		perror("connect");
		return 3;
	}

	char buf[1024];
	while(1)
	{
		printf("%s\n",buf);
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf)-1);
		buf[s-1] = 0;
		write(sock, buf, sizeof(buf)-1);
	}
	close(sock);

	return 0;
}
