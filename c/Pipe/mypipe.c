/*************************************************************************
	> File Name: mypipe.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 13 May 2017 06:49:35 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[2];

	int ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe failed");
	}
	pid_t id = fork();
	if(id == 0)
	{
		//child
		close(fd[0]);//write -- close read
		int i = 0;
		char* msg = "hello world!";
		while(i < 10)
		{
			ssize_t s = write(fd[1], msg, strlen(msg));
			printf("i am writing! %d\n",i++);
			fflush(stdout);
		}
	}
	else
	{
		//father
	//	close(fd[1]);
	//	char buf[1024];
	//	while(1)
	//	{
	//		ssize_t s = read(fd[0], buf, sizeof(buf));
	//		if(s > 0)
	//		{
	//			buf[s] = 0;
	//			printf("father read: %s\n", buf);
	//		}
	//		if(s == 0)
	//		{
	//			printf("end of file!\n");
	//		}
	//	}

		int status = 0;
		waitpid(id, &status, 0);
	}

	return 0;
}
