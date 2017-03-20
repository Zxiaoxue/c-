/*************************************************************************
	> File Name: poll.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Mar 2017 10:37:42 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>

#define _SIZE_ 1024

int startup(const char* _ip, int _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);
	socklen_t len = sizeof(local);

	if(bind(sock, (struct sockaddr*)&local, len) < 0)
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

static void Init_fd(struct pollfd* pfd, int len)
{
	assert(pfd);
	int i = 0;
	for(; i<len; i++)
	{
		pfd[i].fd = -1;
		pfd[i].events = 0;
		pfd[i].revents = 0;
	}
}

static int Add_fd(struct pollfd* pfd, int len, int add_fd)
{
	assert(pfd);
	int i = 0;
	for(; i<len; i++)
	{
		if(pfd[i].fd == -1)
		{
			pfd[i].fd = add_fd;
			return i;
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]", argv[0]);
		return 4;
	}
	int listen_sock = startup(argv[1], atoi(argv[2]));

	struct pollfd pfd[_SIZE_];
	Init_fd(pfd, _SIZE_);
	
	int index = Add_fd(pfd, _SIZE_, listen_sock);
	if(index != -1)
	{
		pfd[index].events = POLLIN;
	}

	int timeout = 2000;
	char* buf[1024];
	while(1)
	{
		switch(poll(pfd, _SIZE_, timeout))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("poll");
		//		exit(1);
				break;
			default:
				{
					int i = 0;
					printf("default..\n");
					for(; i<_SIZE_; i++)
					{
						int fd = pfd[i].fd;
						printf("fd: %d\n",fd);
						sleep(1);
						if(fd == listen_sock && (pfd[i].fd & POLLIN))
						{							
							struct sockaddr_in peer;
							socklen_t len =  sizeof(peer);
							int new_sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
							if(new_sock < 0)
							{
								perror("accept");
//								exit(5);
								return 5;
							}
							else if(new_sock > 0)
							{
								printf("get a new client# ip: %s\n", inet_ntoa(peer.sin_addr));
								int newfd = Add_fd(pfd, _SIZE_, new_sock);
								printf("newfd: %d\n",newfd);
								if(newfd != -1)
								{
									pfd[newfd].events = POLLIN;
								}
								else if(newfd == _SIZE_)
								{
									printf("newfd == _SIZE_\n");
									close(newfd);
								}
							}
						}
						else if(fd != -1 && fd != listen_sock && (pfd[i].events & POLLIN))
						{
							printf("read:\n");
							char buf[1024];
							memset(buf, '\0', sizeof(buf));

							ssize_t _s = read(fd, buf, sizeof(buf)-1);
							if(_s > 0)
							{
								buf[_s] = 0;
								printf("buf: %s\n", buf);
							}
							else if(_s == 0)
							{
								printf("client is quit!\n");
								close(pfd[i].fd);
							}
							else
							{
								perror("read");
								continue;
							}
						}//else if
					}
				}
		}
	}
	return 0;
}
