/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 13 May 2017 07:26:10 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int ret = mkfifo("./mypipe", S_IFIFO | 0666);
	if(ret < 0)
	{
		perror("mkfifo failed!");
		return 1;
	}

	int fd = open("./mypipe", O_RDONLY);
	if(fd < 0)
	{
		perror("open failed!");
		return 2;
	}
	else
	{
		while(1)
		{
			char buf[1024];
			memset(buf, '\0', sizeof(buf));
			ssize_t s = read(fd, buf, sizeof(buf));
			if(s > 0)
			{
				buf[s-1] = 0;
				printf("server read:%s", buf);
			}
			else if(s == 0)
			{
				printf("client closed!server is closing!\n");
				break;
			}
		}
	}
	return 0;
}
