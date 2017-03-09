/*************************************************************************
	> File Name: sleep.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Thu 23 Feb 2017 05:13:35 AM PST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void alarmRun()
{
	//DONOTHING
}
int mysleep(int secs)
{
	struct sigaction act,oact;
	act.sa_handler = alarmRun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oact);
	alarm(secs);
	pause();
	int ret = alarm(0);
	sigaction(SIGALRM, &oact, NULL);

	return ret;//ret > 0 ? /ret == 0 ?
}

int main()
{
	while(1)
	{
		mysleep(1);
		printf("my sleep !\n");
	}
	return 0;
}
