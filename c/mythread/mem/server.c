/*************************************************************************
	> File Name: server.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 17 Feb 2017 05:49:34 AM PST
 ************************************************************************/

#include"comm.h"

int main()
{
	int shmid = creatShm();
	char* mem = (char*)shmat(shmid, NULL, 0);

	while(1)
	{
		sleep(1);
		printf("%s\n",mem);
	}
	//int ret = shmdt(mem);
//	if(ret < 0)
//	{
//		printf("ret is %d\n",ret);
//	}
//		sleep(5);
    dtShm(mem);
	sleep(5);
	destoryShm(shmid);
	return 0;
}
