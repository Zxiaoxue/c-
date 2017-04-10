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
	printf("get_line! buf:%s\n", buf);
	return i;
}

static int echo_www(int sock, const char* path, ssize_t _s)
{
	int ret = 0;
	int fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		echo_errno(sock, 404);
		ret = 8;
	}
	char line[SIZE];
	sprintf(line, "HTTP/1.0 200 OK\r\n");
	send(sock, line, strlen(line), 0);
	send(sock, "\r\n", strlen("\r\n"), 0);

	if(sendfile(sock, fd, NULL, _s) < 0)
	{
		echo_errno(sock, 404);
		ret = 9;
	}
	close(fd);
	return ret;
}

void show_404(int sock)
{
	char* status_line = "errno: 404,not found!\r\n";
	send(sock, status_line, strlen(status_line), 0);
	send(sock, "\r\n", strlen("\r\n"), 0);
}

static echo_errno(int sock, int errno)
{
	switch(errno)
	{
		case 404:
			show_404(sock);
			break;
default:
			break;
	}

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

int excu_cgi(int sock, const char* method,const char*  path, const char* query_string)
{
	printf("cgi is runing! method:%s", method);
	char buf[SIZE];
	char method_env[SIZE/8];
	char query_string_env[SIZE/8];
	char content_len_env[SIZE/8];
	int content_len = -1;

	if(strcasecmp(method, "GET") == 0)
	{//GET
		clear_hander(sock);
	}
	else //POST
	{
		int ret = 0;
		do
		{
			ret = get_line(sock, buf, sizeof(buf)-1);
			if(ret > 0 && strncmp(buf, "Content-Length: ", 16) == 0)
			{
				content_len = atoi(buf+16);
			}
		}while(ret != 1 && strcmp(buf, "\n") != 0);

		if(content_len < 0)
		{
			//echo_errno();
			return 10;
		}//fi
	}//else

	const char* status_line = "HTTP/1.0 200 OK \r\n\r\n";
	send(sock, status_line, strlen(status_line), 0);
	const char* content_type = "Content_Type: text/html\r\n";
	send(sock, content_type, strlen(content_type), 0);
	send(sock, "\r\n", strlen("\r\n"), 0);

	int input[2];	//pipe
	int output[2];	//pipe
	
	pipe(input);
	pipe(output);

	pid_t id = fork();
	if(id < 0)
	{
		printf_log("fork failed!", FATAL);
		//echo_errno();
		return 11;
	}
	else if(id == 0) //child
	{
		close(input[1]);
		close(output[0]);
		close(sock);
		dup2(input[0], 0);
		dup2(output[1], 1);

		printf("path:%s", path);
		sprintf(method_env, "METHOD=%s", method);
		putenv(method_env);

		if(strcasecmp(method, "GET") == 0)
		{
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}
		else
		{
			sprintf(content_len_env, "CONTENT_LENGTH=%d", content_len);
			putenv(content_len_env);
		}

		execl(path, path, NULL);
		exit(1);
	}
	else //father
	{
		close(input[0]);
		close(output[1]);

		char ch = '\0';
		if(strcasecmp(method ,"POST") == 0)
		{
			int i = 0;
			for(; i<content_len; i++)
			{
				recv(sock, &ch, 1, 0);
				write(input[1], &ch, 1);
			}
		}
		ch = '\0';
		while(read(output[0], &ch, 1) > 0)
		{
			send(sock, &ch, 1, 0);
		}
		waitpid(id, NULL, 0);
	}
}
int hander_pthread(int sock)
{
	char buf[SIZE];
	char method[64];
	char url[SIZE];
	char path[SIZE];
	char c = '\0';

	memset(buf, '\0', sizeof(buf));
	memset(method, '\0', sizeof(method));
	memset(url, '\0', sizeof(url));
	memset(path, '\0', sizeof(path));
	
	int i = 0;
	int j = 0;
	int cgi = 0;
	int ret = 0;
	char* query_string = NULL;

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
	
	if(query_string != NULL &&*query_string == '?')
	{
		*query_string ='\0';
		query_string++;
		cgi = 1;
	}

	sprintf(path, "wwwroot%s", url);
	if(path[strlen(path)-1] == '/')
	{
		//printf("path[strlen(path)-1] == '/'\n");
		strcat(path, "index.html");
	}

	printf("hander_pthread! buf:%s\n", buf);
	printf("hander_pthread! method:%s\n", method);
	printf("hander_pthread! url:%s\n", url);
	printf("hander_pthread! path:%s\n", path);
	
	struct stat st;
	if(stat(path, &st) < 0)
	{
		printf("stat failed!\n");
		echo_errno(sock, 404);
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
			ret = excu_cgi(sock, method, path, query_string);
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
