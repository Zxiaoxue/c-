/*************************************************************************
	> File Name: myshell.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Fri 12 May 2017 06:39:18 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t id = fork();
	if(id == 0)
	{
		execlp(_argv[0], _argv);
		exit(0);
	}
	else
	{
		while(1)
		{
			printf("[myshell@myhostname test]# ");
			fflush(stdout);

			char buf[1024];
			ssize_t s = read(0, buf, sizeof(buf)-1);
			if(s > 0)
			{
				buf[s-1] = 0;
			}
			//string ls -n -i -a
			char* _argv[32];
			char* start = buf;
			_argv[0] = buf;
			int i = 0;
			while(*start)
			{
				if(*start == ' ')
				{
					*start = 0;
					start++;
					_argv[i++] = start;
				}
				else
				{
					start++;
				}
			}

			_argv[i] = NULL;
		}
	}

	return 0;
}
