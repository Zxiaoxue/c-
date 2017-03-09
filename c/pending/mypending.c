/*************************************************************************
	> File Name: mypending.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Thu 23 Feb 2017 02:46:35 AM PST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void printPending(sigset_t *pending)
{
	int i = 1;
	for(; i<=31; i++)
	{
		if( sigismember(pending,i))
		{
			printf("1");
		}
		else
			printf("0");
	}
	printf("\n");
}

void intRun(sigset_t *s)
{
	printf("catch 2 signal\n");
}

int main()
{
//	struct sigaction act, oact;
//	act.sa_handler = SIG_IGN;
//	act.sa_flags = 0;
//	sigemptyset(&act.sa_mask);
//	sigaction(SIGINT, &act, &oact);
//
//	int ret = pause();
//	printf("pause return: %d\n",ret);
//
	signal(SIGINT, intRun);
	sigset_t block, oblock, pending;

	sigempty(&block);
	sigprocmask(SIG_BLOCK, &block, &oblock);



//	sigset_t s;
//	sigemptyset(&s);
//	sigaddset(&s,SIGINT);
//	sigprocmask(SIG_BLOCK, &s, NULL);
//	
//	while(1)
//	{
//		sleep(1);
//		sigpending(&s);
//		printPending(&s);
//	}


	return 0;
}
