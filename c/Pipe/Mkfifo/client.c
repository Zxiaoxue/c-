/*************************************************************************
	> File Name: client.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 13 May 2017 07:26:10 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("./mypipe", O_WRONLY);
	if(fd < 0)
	{
		perror("open failed!");
		return 1;
	}
	else
	{
		while(1)
		{
			printf("Please Enter: ");
			fflush(stdout);
			char msg[1024];
			memset(msg, '\0', sizeof(msg)-1);
			ssize_t s = read(0, msg, sizeof(msg));
			write(fd, msg, sizeof(msg));
		}
	}
	return 0;
}
