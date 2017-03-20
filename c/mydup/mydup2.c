/*************************************************************************
	> File Name: mydup2.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 19 Mar 2017 06:41:07 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	int fd = open("./log", O_CREAT|O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	close(1);
	int new_fd = dup2(fd, 1);
	if(new_fd == -1)
	{
		perror("dup2");
		return 2;
	}
	int i = 0;
	while(i++<10)
	{
		printf("hello bit! i: %d\n",i);
		fflush(stdout);
	}
	close(new_fd);
	return 0;
}
