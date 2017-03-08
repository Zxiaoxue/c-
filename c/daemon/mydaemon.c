/*************************************************************************
	> File Name: mydaemon.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 24 Feb 2017 11:39:22 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void Deamon()
{
	umask(0);

	if(fork() > 0)
	{
		exit(0);
	}
	setsid();

	chdir("/");

	close(0);
	close(1);
	close(2);

	signal(SIGCHLD,SIG_IGN);

}


int main()
{
	//Deamon();

	while(1)
	{
		sleep(1);
	}
	return 0;
}
