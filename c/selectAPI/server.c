/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Wed 15 Mar 2017 02:15:31 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define _SIZE_ 128
int gfd[_SIZE_];


int statup(const char* _ip, int _port)
{
	assert(_ip);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
		exit(1);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(2);
	}

	if(listen(sock, 5) < 0)
	{
		perror("listen");
		exit(3);
	}

	return sock;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]",argv[0]);
		exit(4);
	}

	int listen_sock = statup(argv[1],atoi(argv[2]));
	//shezhiweiwuxiao
	int i = 0;
	for(; i<_SIZE_; i++)
	{
		gfd[i] = -1;
	}

	int index = 0;
	gfd[index++] = listen_sock;



	while(1)
	{
		struct timeval timeout = {5,0};
		fd_set rfds;
		FD_ZERO(&rfds);//clear rfds

		int j = 0;
		int max_fd = -1;
		for(; j<_SIZE_; j++)
		{
			if(gfd[j] > 0)
			{
				FD_SET(gfd[j], &rfds);
				if(max_fd < gfd[j])
				{
					max_fd = gfd[j];
				}
			}
		}

		switch(select(max_fd+1, &rfds, NULL, NULL, &timeout))
		{
			case 0:
				perror("time out");
				break;
			case -1:
				perror("select");
				break;
			default:
				{
					int k = 0;
					for(; k<_SIZE_; k++)
					{
						if(gfd[k] < 0)
						{
							continue;
						}
						if(k==0 && FD_ISSET(listen_sock, &rfds))
						{
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
							if(sock < 0)
							{
								perror("accept");
								exit(5);
							}
							if(sock > 0)
							{
								printf("get a new client ip:%s port:%d\n",inet_ntoa(peer.sin_addr),\
										ntohs(peer.sin_port));
								int m = 0;
								for(; m<_SIZE_; m++)
								{
									if(gfd[m] == -1)
									{
										gfd[m] = sock;
										break;
									}

								}
								if(m == _SIZE_)
								{
									printf("m == _SZIE_\n");
									close(sock);
								}
							}
						}
						else if(FD_ISSET(gfd[k], &rfds))
						{
							char buf[1024];
							memset(buf, 0, sizeof(buf)-1);
							ssize_t _s = read(gfd[k], buf, sizeof(buf)-1);
							if(_s > 0)
							{
								printf("client# %s\n", buf);
							}
							else if(_s == 0)
							{
								printf("client is quit...\n");
								close(gfd[k]);
								gfd[k] = -1;
							}
							else
							{
								perror("read");
							}

						}
					}
				}
				break;
		}

	}
	return 0;
}
