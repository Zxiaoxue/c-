/*************************************************************************
	> File Name: mydup.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 19 Mar 2017 06:18:49 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd = open("./log", O_CREAT| O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	close(1);
	int new_fd = dup(fd);
	if(fd == -1)
	{
		perror("dup");
		return 2;
	}
	close(fd);


	char buf[1024];
	int i = 0;
	while(i++<10)
	{
		//ssize_t _s = read(new_fd, buf, sizeof(buf)-1);
		//if(_s < 0)
		//{
		//	perror("read");
		//	return 3;
		//}
		//
		printf("hello world! %d\n",i);
		//printf("buf: %s\n",buf);
		fflush(stdout);
	}
	close(new_fd);
	return 0;
}
