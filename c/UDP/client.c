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
	//printf("I am client!\n");
	if( argc != 3)
	{
		printf("Usage: %s [server_ip] [server_port]",argv[0]);
		return 1;
	}

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}


	char buf[1024];
	int buflen = sizeof(buf);
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr = inet_addr(argv[1]);
	peer.sin_port = htons(atoi(argv[2]));
	socklen_t len = sizeof(peer);

	while(1)
	{
		printf("Please Enter# ");
		fflush(stdout);

		ssize_t _s = read(0, buf, sizeof(buf)-1);
	
		buf[_s-1] = 0;
		ssize_t s = sendto(sock, buf, buflen, 0, (struct sockaddr*)&peer, len);
		if(s < 0)
		{
			perror("sendto");
			return 4;
		}

	//	printf("server# %s\n", buf);
	}

	close(sock);
	return 0;
}
