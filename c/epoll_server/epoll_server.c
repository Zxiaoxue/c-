/*************************************************************************
	> File Name: epoll_server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 18 Mar 2017 10:21:03 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<stdlib.h>
#include<string.h>

#define _SIZE_ 1024

typedef struct epbuf
{
	int fd;
	char buf[_SIZE_];
}epbuf_t,*epbuf_p,**epbuf_pp;

static epbuf_p alloc_epbuf(int fd)
{
	epbuf_p ptr = (epbuf_p)malloc(sizeof(epbuf_t));
	if(ptr == NULL)
	{
		perror("malloc");
		exit(6);
	}
	ptr->fd = fd;
	printf("ptr->fd:%d\n",fd);
	return ptr;
}
static void delete_epbuf(epbuf_p ptr)
{
	if(ptr != NULL)
	{
		free(ptr);
	}
	ptr = NULL;
}

int startup(const char* _ip, int _port)
{
	assert(_ip);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
		exit(1);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);
	socklen_t len = sizeof(local);

	if(bind(sock, (struct sockaddr*)&local, len) < 0)
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

int  main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]",argv[0]);
		return 4;
	}

	int epfd = epoll_create(256);
	if(epfd < 0)
	{
		perror("epoll_create");
		return 5;
	}
	int listen_sock = startup(argv[1], atoi(argv[2]));

	struct epoll_event _ev;
	_ev.events = EPOLLIN;
	_ev.data.ptr = alloc_epbuf(listen_sock);
	_ev.data.fd = listen_sock;
	
	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &_ev);

	struct epoll_event _evs[32];
	int max = 32;
	int timeout = 2000;
	int nums = 0;
	while(1)
	{
		switch(nums = epoll_wait(epfd, _evs, max, timeout))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("epoll_wait");
				break;
			default:
				{
					printf("nums: %d\n",nums);
					int i = 0;
					for(; i<nums; i++){
						sleep(1);
						int fd = (epbuf_p)(_evs[i].data.ptr)->fd;
						printf("after fd: %d\n",fd);
						if(fd == listen_sock && (_evs[i].events & EPOLLIN)){
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							int new_sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
							printf("after accept,new_sock:%d\n",new_sock);
							if(new_sock < 0){
								perror("accept");
								continue;
							}
							else if(new_sock > 0){
								printf("get a new client# port %d\n",ntohs(peer.sin_port));
								_ev.events = EPOLLIN;
								_ev.data.fd = new_sock;
								_ev.data.ptr = alloc_epbuf(new_sock);
								epoll_ctl(epfd, EPOLL_CTL_ADD, new_sock, &_ev);
							}
						}//if
						else if(fd != listen_sock && (_evs[i].events & EPOLLIN))
						{
							char* buf = ((epbuf_p)(_evs[i].data.ptr))->buf;
							printf("read  fd: %d\n",fd);
							ssize_t _s = read(fd, buf, _SIZE_-1);
							if(_s > 0){
								//succeed, change file descriptor
								buf[_s] = 0;
								printf("%s\n", buf);
								_ev.events = EPOLLOUT;
								epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &_ev);
							}
							else  if(_s == 0){
								printf("client is quit!\n");
								delete_epbuf(_evs[i].data.ptr);
								_evs[i].data.ptr = NULL;
								epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
								close(fd);
							}
							else{
								perror("read");
								continue;
							}
						}//else if   read file descriptor
					//	else if(fd != listen_sock && (_evs[i].events & EPOLLOUT))
					//	{
					//		const char* msg = "HTTP/1.0 200 OK \r\n\r\n<html><h1>HELLO WORLD!</h1></html>\n";
					//		write(fd, msg, strlen(msg));
					//		delete_epbuf(_evs[i].data.ptr);
					//		_evs[i].data.ptr = NULL;
					//		epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
					//		close(fd);
					//	}//else if   write file descriptor
					}//for
				}
				break;
		}//switch

	}//while
	return 0;
}
