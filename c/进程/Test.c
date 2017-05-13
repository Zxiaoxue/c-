/*************************************************************************
	> File Name: Test.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 12 May 2017 06:31:29 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define _PROC_NUM_ 10
#define _DEFAULT_PID_ -1


int child_run()
{
	srand(time(NULL));
	int _time = rand()%30;
	printf("hello bit!this child pid is:%d,sleep time long is:%d\n",getpid(),_time);
	sleep(_time);
	return 0;
}

//success ret 1,else 0
int creat_proc(pid_t*_pid_l,int _num)
{
	if(_pid_l != NULL && _num > 0)
	{
		int i = 0;
		for(;i<_num;i++)
		{
			pid_t id = fork();
			if(id < 0)
			{
				printf("%s:creat proc failed\n");
				return 1;
			}
			else if(id == 0)
			{//child
				int child_ret = child_run();
				exit(1);
			}
			else
			{//father
				_pid_l[i] = id;
			}
		}
	}
	return 0;
}

//return 0,success else return 1
int wait_proc(pid_t* _pid_l,int _num)
{
	int _wait_ret = 0;
	if(_pid_l != NULL && _num > 0)
	{
		int i = 0;
		for(; i<_num; i++)
		{
			if(_pid_l[i] == _DEFAULT_PID_)
			{
				continue;
			}
			int status = 0;
			int ret = waitpid(_pid_l[i], &status, 0);
			if(WIFEXITED(status) && ret == _pid_l[i])
			{
				printf("wait child pid %d success, return code is:%d\n",_pid_l[i], WEXITSTATUS(status));
			}
			else
			{
				printf("wait child pid %d failed!\n",_pid_l[i]);
				_wait_ret = 1;
			}
		}
	}
	return _wait_ret;
}

int main()
{
	pid_t _pid_list[_PROC_NUM_];
	int i = 0;
	for(; i<_PROC_NUM_; i++)
	{
		_pid_list[i] = _DEFAULT_PID_;
	}
	if(creat_proc(_pid_list, sizeof(_pid_list)/sizeof(_pid_list[0])) == 0)
	{
		printf("%s:create all proc success!\n",__FUNCTION__);
	}
	else
	{
		printf("%s:not all proc create success!\n",__FUNCTION__);
	}
	if(wait_proc(_pid_list, sizeof(_pid_list)/sizeof(_pid_list[0])) == 0)
	{
		printf("%s:wait all proc success!\n",__FUNCTION__);
	}
	else
	{
		printf("%s:not all proc success!\n",__FUNCTION__);
	}
	return 0;
}


//int main()
//{
//	pid_t id = fork();
//	if(id < 0)
//	{
//		printf("fork error\n");
//		return 1;
//	}
//	else if(id == 0)
//	{
//		//child
//		printf("child is runing, pid is %d\n",getpid());
//		sleep(5);
//		exit(257);
//	}
//	else
//	{
//		//father
//		int status = 0;
//		pid_t ret = 0;
//		//ret = waitpid(-1, &status, 0);
//		do
//		{
//			ret = waitpid(-1, &status, WNOHANG);
//			if(ret == 0)
//				printf("father is runing,pid is %d\n",getpid());
//			sleep(1);
//		}while(ret == 0);
//		//printf("this is test for wait\n");
//		if(WIFEXITED(status) && ret == id)
//		{
//			printf("wat child 5s success, child return code is:%d\n",WEXITSTATUS(status));
//		}
//		else
//		{
//			printf("wait child failed!\n");
//			return 2;
//		}
//	}
//	return 0;
//}

//int glob = 6;
//char buf[] = "a write to stdout\n";

//int g_val = 0;
//
//void fun()
//{
//	printf("child exit\n");
//}
//
//int main()
//{
//	pid_t id = fork();
//
//	while(1)
//	{
//		if(id < 0)
//		{
//			exit(1);
//		}
//		else if(id == 0)
//		{
//			printf("child is start!\n");
//			sleep(3);
//		}
//		else
//		{
//			printf("father is start!\n");
//			sleep(3);
//			wait(NULL);
//		}
//	}
//	return 0;
//	int _val = 0;
//	pid_t id = vfork();
//	if(id < 0)
//	{
//		exit(1);
//	}
//	else if(id == 0)
//	{
//		atexit(fun);
//		printf("this is chils process.\n");
//		++g_val;
//		++_val;
//		sleep(3);
//		exit(0);
//	}
//	else
//	{
//		printf("this is father process.\n");
//		printf("father exit, g_val=%d, _val=%d\n",g_val,_val);
//	}
//	
//	return 0;
//	
	//int var;

	//pid_t pid;
	//var = 88;
	//if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1)
	//	perror("write error");
	//printf("before fork\n");

	//if((pid = fork()) < 0)
	//{
	//	perror("fork error");
	//}
	//else if(pid == 0)
	//{//child
	//	glob++;
	//	var++;
	//}
	//else
	//{//father
	//	sleep(2);
	//}

	//printf("pid = %d, glob = %d, var = %d\n",getpid(),glob,var);
	//exit(0);
//	while(1)
//	{
//		if(id == 0)
//		{
//			printf("child is start!\n");
//			sleep(1);
//		}
//		else
//		{
//			printf("father is start!\n");
//			int* status = NULL;
//			pid_t pid = wait(status);
//			sleep(2);
//		}
//	}
//	return 0;
//}
