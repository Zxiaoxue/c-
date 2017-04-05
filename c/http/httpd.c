/*************************************************************************
	> File Name: httpd.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 01 Apr 2017 11:53:41 PM PDT
 ************************************************************************/
#ifndef _HTTPD_H_
#define _HTTPD_H_
#include"httpd.h"


void printf_log(const char* msg, int i)
{
	printf("[%s] [%d]\n",msg, i);
}

int get_line(int sock, char* buf, size_t len)
{
	assert(buf);
	char c = '\0';
	int i = 0;
	while(i < len-1 && c != '\n')
	{
		ssize_t s = recv(sock, &c, 1, 0);
		if(s > 0)
		{
			if(c == '\r')
			{
				s=recv(sock, &c, 1, MSG_PEEK);//kuitan
				if(s > 0 && c == '\n')
				{
					s = recv(sock, &c, 1, 0);
				}
				else
					c = '\n';
			}
		}
		buf[i++] = c;
	}
	buf[i] = '\0';
	
//	printf("1111111111111111111111111\n");
//	printf("get_line! buf:%s\n", buf);
	return i;
}

static int echo_www(int sock, const char* path, ssize_t _s)
{
	int ret = 0;
	int fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		//echo_errno();
		ret = 8;
	}
	char line[SIZE];
	sprintf(line, "HTTP/1.0 200 OK\r\n");
	send(sock, line, strlen(line), 0);
	send(sock, "\r\n", strlen("\r\n"), 0);

	if(sendfile(sock, fd, NULL, _s) < 0)
	{
		//echo_errno();
		ret = 9;
	}
	close(fd);
	return ret;
}

static void clear_hander(int sock)
{
	char line[SIZE];
	int ret = 0;

	do
	{
		ret = get_line(sock, line, sizeof(line));
	}
	while(ret != 1 && strcmp(line, "\n") != 0);
}

int handle_pthread(int sock)
{
	char buf[SIZE];
	char method[64];
	char url[SIZE];
	char path[SIZE];
	char c = '\0';

	int i = 0;
	int j = 0;
	int cgi = 0;
	int ret = 0;
	char* query_string = NULL;

	//printf("hander_pthread!\n");
	ret = get_line(sock, buf, sizeof(buf));
	if(ret < 0)
	{
		printf_log("get_line failed!", FATAL);
		ret = 6;
		goto end;
	}

	while(i<sizeof(method)-1 && j<sizeof(buf)-1 && !isspace(buf[j]))
	{
		method[i] = buf[j];
		i++,j++;
	}
	method[i] = '\0';

	if(strcasecmp(method, "POST") != 0 && strcasecmp(method, "GET") != 0)
	{
		printf_log("the header error!", FATAL);
		ret = 7;
		goto end;
	}

	while(isspace(buf[j]) && j< sizeof(buf)-1)
	{
		j++;
	}

	if(strcasecmp(method, "POST") == 0)
	{
		cgi = 1;
	}

	i=0;
	while(i<sizeof(url)-1 && j<sizeof(buf)-1 &&  !isspace(buf[j]))
	{
		url[i] = buf[j];
		i++,j++;
	}
	url[i] = '\0';

	if(strcasecmp(method, "GET") == 0)
	{
		query_string = url;
		while(*query_string != '\0' && *query_string != '?')
		{
			query_string++;
		}

	}
	
	if(*query_string == '?')
	{
		*query_string ='\0';
		query_string++;
		cgi = 1;
	}

	sprintf(path, "wwwroot%s", url);

//	printf("hander_pthread! buf:%s\n", buf);
//	printf("hander_pthread! method:%s\n", method);
//	printf("hander_pthread! url:%s\n", url);
//	printf("hander_pthread! path:%s\n", path);


	if(path[strlen(path)-1] != '/')
	{
		strcat(path, "index.html");
	}
	struct stat st;
	if(stat(path, &st) < 0)
	{
		//echo_errno();
		ret = 8;
		goto end;
	}
	else
	{
		if(S_ISDIR(st.st_mode))
		{
			strcat(path, "/index.html");
		}
		else if(st.st_mode & S_IXUSR || st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
		{
			cgi = 1;
		}

		if(cgi)
		{
			//excu_cgi(sock, method, path, query_string);
		}
		else
		{
			clear_hander(sock);
			ret = echo_www(sock, path, st.st_size);
		}
	}
end:
	close(sock);
	return ret;
}


int startup(const char* _ip, int _port)
{

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		printf_log("socket failed!", FATAL);
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);
	socklen_t len = sizeof(local);

	if(bind(sock, (struct sockaddr*)&local, len) < 0)
	{
		printf_log("bind failed!", FATAL);
		exit(3);
	}

	if(listen(sock,5) < 0)
	{
		printf_log("listen failed!",FATAL);
		exit(4);
	}
	printf_log("listen success!",NORMAL);
	return sock;
}

#endif //_HTTPD_H_
