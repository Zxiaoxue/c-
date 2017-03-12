/*************************************************************************
	> File Name: client.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Feb 2017 12:51:38 AM PST
 ************************************************************************/

#include<stdio.h>
#include"comm.h"
int main()
{
	int shmid = getShm();

	char* mem = (char *)shmat(shmid, NULL, 0);
	int i = 0;
	while(1)
	{
		sleep(1);
		mem[i++] = 'A';
		i %= (SIZE-1);
		mem[i] = '\0';
	}

	dtShm(mem);
	return 0;
}
