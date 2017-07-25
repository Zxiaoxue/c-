/*
 * (C) Radim Kolar 1997-2004
 * This is free software, see GNU Public License version 2 for
 * details.
 *
 * Simple forking WWW Server benchmark:
 *
 * Usage:
 *   webbench --help
 *
 * Return codes:
 *    0 - sucess
 *    1 - benchmark failed (server is not on-line)
 *    2 - bad param
 *    3 - internal error, fork failed
 * 
 */ 
#include "socket.c"
#include <unistd.h>
#include <sys/param.h>
#include <rpc/types.h>
#include <getopt.h>
#include <strings.h>
#include <time.h>
#include <signal.h>

#define METHOD_GET 0
#define METHOD_HEAD 1
#define METHOD_OPTIONS 2
#define METHOD_TRACE 3
#define PROGRAM_VERSION "1.5"
#define REQUEST_SIZE 2048

/* values */
volatile int timerexpired=0;//判断压测试时长是否已经达到设定时间
int speed=0;//进程成功得到服务器相应的数量
int failed=0;//失败的数量(speed代表成功，failed代表失败)
int bytes=0;//进程成功从服务器读取的字节数

/* globals */
int http10=1; /* http版本，0代表http/0.9, 1代表http/1.0, 2代表http/1.1 */

/*请求方法：GET, HEAD, OPTIONS, TRACE */

int method=METHOD_GET;//默认为GET方法
int clients=1;		//发起请求的客户端数目，默认为1，可以通过-c/-client选项设置
int force=0;			//是否需要等待读取从server返回的数据，0表示等待读取
int force_reload=0;	//是否使用缓存，1表示不缓存，0表示缓存-----是否重新请求
int proxyport=80;		//代理服务器端口号
char *proxyhost=NULL;//代理服务器IP，初始化为NULL
int benchtime=30;		//压测时间，默认为30秒，可以通过-t/-time选项设置

/* internal */
int mypipe[2];
char host[MAXHOSTNAMELEN];	//服务器端ip
char request[REQUEST_SIZE];	//保存请求报文，(请求行，请求报头，空行，请求正文)

/*
struct option {
	const char *name;
	int has_arg;
    int *flag;
    int val;
};
struct option结构体中元素解释如下：
1.const char *name;	//选项名

2.int has_arg;		//描述长选项是否有选项参数
has_arg有3个值，
符号常量			 数值			含义
no_argument		  0		表示该选项后面不跟参数值，
required_argument  1		表示该选项后面一定跟参数值，		
optional_argument  2		表示该选项后面可以跟，也可以不跟参数值

3.int* flag;			//用来决定，getopt_long()的返回值到底是什么，
如果flag为NULL，则函数会返回与该项option匹配的val值，
如果flag不是NULL，则将val值赋予flag所指向的内存，并且返回0

4.int val;			//如果flag为NULL，那么val通常是个字符常量，
如果短选项与长选项一致，那么该字符就应该与optstring中出现的这个选项的参数相同
*/

//struct option结构体初始化
static const struct option long_options[]=
{
 {"force",no_argument,&force,1},
 {"reload",no_argument,&force_reload,1},
 {"time",required_argument,NULL,'t'},
 {"help",no_argument,NULL,'?'},
 {"http09",no_argument,NULL,'9'},
 {"http10",no_argument,NULL,'1'},
 {"http11",no_argument,NULL,'2'},
 {"get",no_argument,&method,METHOD_GET},
 {"head",no_argument,&method,METHOD_HEAD},
 {"options",no_argument,&method,METHOD_OPTIONS},
 {"trace",no_argument,&method,METHOD_TRACE},
 {"version",no_argument,NULL,'V'},
 {"proxy",required_argument,NULL,'p'},
 {"clients",required_argument,NULL,'c'},
 {NULL,0,NULL,0}
};

/* prototypes */
static void benchcore(const char* host,const int port, const char *request);
static int bench(void);
static void build_request(const char *url);

/*信号处理函数，当测试时间完成时产生SIGALARM信号，，调用此函数，将timerexpried置为1，表示子进程需要退出
在后面的函数调用时会看到，在程序的while循环中会不断检测此值，只有timerexpired为1时，程序才会跳出while循环
并返回*/
static void alarm_handler(int signal)
{
   timerexpired=1;//timerexpired:判断压测时长是否已经达到设定时间
}	

/*
usage函数：webbench用法介绍
	-f|--force               不需要等待服务器响应
	-r|--reload              发送重新加载请求
	-t|--time <sec>          运行多长时间，单位是秒
	-p|--proxy <server:port> 使用代理服务器发送请求
	-c|--clients <n>         创建多少个客户端
	-9|--http09              使用HTTP/0.9
	-1|--http10              使用HTTP/1.0协议
	-2|--http11              使用HTTP/1.1协议
	--get                    使用GET方法请求
	--head                   使用HEAD方法请求
	--options                使用OPTIONS方法请求
	--trace                  使用TRACE方法请求
	-?|-h|--help             打印帮助信息
	-V|--version			   显示版本号

*/

static void usage(void)
{
   fprintf(stderr,
	"webbench [option]... URL\n"
	"  -f|--force               Don't wait for reply from server.\n"
	"  -r|--reload              Send reload request - Pragma: no-cache.\n"
	"  -t|--time <sec>          Run benchmark for <sec> seconds. Default 30.\n"
	"  -p|--proxy <server:port> Use proxy server for request.\n"
	"  -c|--clients <n>         Run <n> HTTP clients at once. Default one.\n"
	"  -9|--http09              Use HTTP/0.9 style requests.\n"
	"  -1|--http10              Use HTTP/1.0 protocol.\n"
	"  -2|--http11              Use HTTP/1.1 protocol.\n"
	"  --get                    Use GET request method.\n"
	"  --head                   Use HEAD request method.\n"
	"  --options                Use OPTIONS request method.\n"
	"  --trace                  Use TRACE request method.\n"
	"  -?|-h|--help             This information.\n"
	"  -V|--version             Display program version.\n"
	);
};
int main(int argc, char *argv[])
{
	int opt=0;
	int options_index=0;
	char *tmp=NULL;

	if(argc==1)
	{
		usage();
		return 2;
	} 

 /*getopt_long函数
函数功能：用来解析命令行参数，参数argc和argv分别代表参数个数和内容，跟main函数里的命令行参数一样
int getopt_long(int argc, char* argv[], const char* optstring, const struct option* longopts, int* longindex);
参数optstring：为选项字符串，告诉getopt可以处理那个选项以及哪个选项需要参数，如果选项字符串里的字母接着冒号: ":"，
则表示还有相关的参数，全局变量optarg即会指向此额外参数，如果在处理期间遇到了不符合optstring指定的其它选项，
getopt将会显示一个错误消息，并将全局变量设置为"?"字符将全局变量设置为0则不会打印出错信息。
返回值：每次调用该函数，它都会分析一个选项，并且返回它的短选项，如果分析完毕，即没有选项了，则会返回-1
*/
	while((opt=getopt_long(argc,argv,"912Vfrt:p:c:?h",long_options,&options_index))!=EOF )
	{
	 /*
	 #include<unistd.h>
	 extern char* optarg;//选项的参数指针
	 extern int optind;  //下一次调用getopt_long时，从optind存储的位置处重新开始检查选项
	 extern int opterr;  //当opterr=0时，getopt_long不向stderr输出错误信息
	 extern int optopt;  //当命令行选项字符不包括在optstring中或缺少必要参数时，该选项存储在optopt中，
						 getopt_long返回'?'*/
		switch(opt)
		{
		case  0 : break;
		case 'f': force=1;break;
		case 'r': force_reload=1;break; 
		case '9': http10=0;break;
		case '1': http10=1;break;
		case '2': http10=2;break;
		case 'V': printf(PROGRAM_VERSION"\n");exit(0);
		case 't': benchtime=atoi(optarg);break;	     //optarg是选项的参数指针，-t选项后跟的是运行时长
		case 'p': //返回字符'p'，说明使用代理服务器
	     /* proxy server parsing server:port */
		 /*代理服务器解析：IP:Port  eg: 192.168.237.128:8080  */
			tmp=strrchr(optarg,':');//tmp = ":8080"
			proxyhost=optarg;
			if(tmp==NULL)
			{
				break;
			}
			if(tmp==optarg)//tmp == ":8080" == optorg 没有主机IP,只有端口号
			{
				fprintf(stderr,"Error in option --proxy %s: Missing hostname.\n",optarg);
				return 2;
			}
			if(tmp==optarg+strlen(optarg)-1)//org == "192.168.237.128:" == tmp, 没有代理服务器端口号
			{
				fprintf(stderr,"Error in option --proxy %s Port number is missing.\n",optarg);
				return 2;
			}
			*tmp='\0';//正常情况 tmp = ":8080" tmp+1 = "8080"
			proxyport=atoi(tmp+1);
			break;
		case ':':
		case 'h':
		case '?': usage();return 2;break;//getopt_long在分析选项时，遇到一个没有定义过的选项，则返回值为'?'
		case 'c': clients=atoi(optarg);break; //这时，optarg指向的参数信息是客户端数目
		}
	}
	if(optind==argc)
	{
		fprintf(stderr,"webbench: Missing URL!\n");
		usage();
		return 2;
	}
	
	if(clients==0)
		clients=1;
	if(benchtime==0)
		benchtime=60;
 /* Copyright */
	fprintf(stderr,"Webbench - Simple Web Benchmark "PROGRAM_VERSION"\n""Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.\n");

	build_request(argv[optind]);//argv[optind]=URL,构造请求报头
 /* print bench info */
 //打印测试的相关信息
	printf("\nBenchmarking: ");
	switch(method)
	{
	case METHOD_GET:
	default:
		printf("GET");break;
	case METHOD_OPTIONS:
		printf("OPTIONS");break;
	case METHOD_HEAD:
		printf("HEAD");break;
	case METHOD_TRACE:
		printf("TRACE");break;
	}
	printf(" %s",argv[optind]);
	switch(http10)
	{
	case 0: printf(" (using HTTP/0.9)");break;
	case 2: printf(" (using HTTP/1.1)");break;
	}
	printf("\n");
	if(clients==1) 
		printf("1 client");
	else
		printf("%d clients",clients);

	printf(", running %d sec", benchtime);
	if(force) 
		printf(", early socket close");
	if(proxyhost!=NULL) 
		printf(", via proxy server %s:%d",proxyhost,proxyport);
	if(force_reload) 
		printf(", forcing reload");
	
	printf(".\n");

 //核心代码
	return bench();
}

//构造请求报头
void build_request(const char *url)
{
	char tmp[10];
	int i;

  /*int bzero(void* s, size_t n);将内存块(字符串s)中的前n个字节置为0，包括'\0'*/
	bzero(host,MAXHOSTNAMELEN);
	bzero(request,REQUEST_SIZE);

  //设置http版本信息
	if(force_reload && proxyhost!=NULL && http10<1) http10=1;
	if(method==METHOD_HEAD && http10<1) http10=1;
	if(method==METHOD_OPTIONS && http10<2) http10=2;
	if(method==METHOD_TRACE && http10<2) http10=2;

  //获得请求方法
	switch(method)
	{
	default:
	case METHOD_GET: strcpy(request,"GET");break;
	case METHOD_HEAD: strcpy(request,"HEAD");break;
	case METHOD_OPTIONS: strcpy(request,"OPTIONS");break;
	case METHOD_TRACE: strcpy(request,"TRACE");break;
	}
	strcat(request," ");

	if(NULL==strstr(url,"://"))
	{
		fprintf(stderr, "\n%s: is not a valid URL.\n",url);
		exit(2);
	}
	if(strlen(url)>1500)
	{
		fprintf(stderr,"URL is too long.\n");
		exit(2);
	}
	if(proxyhost==NULL)
		if (0!=strncasecmp("http://",url,7)) 
		{
			fprintf(stderr,"\nOnly HTTP protocol is directly supported, set --proxy for others.\n");
			exit(2);
		}
  /* protocol/host delimiter */
  // eg: url = "http://www.baidu.com/" --- i = 4-0+3 = 7 这时i指向第一个w的位置
		i=strstr(url,"://")-url+3;

  /* printf("%d\n",i); */
  //此时url+i = "www.baidu.com/", 寻找'/'是否是url+i的子串，因为主机名必须以'/'结尾
		if(strchr(url+i,'/')==NULL) 
		{
			fprintf(stderr,"\nInvalid URL syntax - hostname don't ends with '/'.\n");
			exit(2);
		}
		if(proxyhost==NULL)//没有代理主机
		{
		/* get port from hostname */
		/* index(s, c)函数返回c在s中第一次出现的位置*/
			if(index(url+i,':')!=NULL && index(url+i,':')<index(url+i,'/'))//有代理主机端口号
			{
				//eg：http://www.baidu.com/:8080  strchr(str，val)查找字符串str中首次出现val的位置 
				//把url+i位置开始的21-0-7=14个字符赋值给host host=www.baidu.com/
				strncpy(host,url+i,strchr(url+i,':')-url-i);
				//清空tmp的前10个字节位置	 
				bzero(tmp,10);
				//将端口号放到tmp中去
				strncpy(tmp,index(url+i,':')+1,strchr(url+i,'/')-index(url+i,':')-1);
				/* printf("tmp=%s\n",tmp); */
				proxyport=atoi(tmp);	//将端口号赋值给roxyport
				if(proxyport==0) proxyport=80;
			} 
			else//没有端口号 eg: http://www.baidu.com/
			{
				strncpy(host,url+i,strcspn(url+i,"/"));
			}
			// printf("Host=%s\n",host);
			//#############################################
			//why here using request+strlen(request)?
			strcat(request+strlen(request),url+i+strcspn(url+i,"/"));
		} 
		else //有代理主机
		{
			// printf("ProxyHost=%s\nProxyPort=%d\n",proxyhost,proxyport);
			strcat(request,url);
		}
		if(http10==1)
			strcat(request," HTTP/1.0");
		else if (http10==2)
			strcat(request," HTTP/1.1");
		strcat(request,"\r\n");
		if(http10>0)
			strcat(request,"User-Agent: WebBench "PROGRAM_VERSION"\r\n");
		if(proxyhost==NULL && http10>0)
		{
			strcat(request,"Host: ");
			strcat(request,host);
			strcat(request,"\r\n");
		}
		if(force_reload && proxyhost!=NULL)
		{
			strcat(request,"Pragma: no-cache\r\n");
		}
		//添加Connection:close连接为短连接，一次连接即时关闭
		if(http10>1)
			strcat(request,"Connection: close\r\n");
		/* add empty line at end */
		//添加空行
		if(http10>0) 
			strcat(request,"\r\n"); 
		// printf("Req=%s\n",request);
}

/* vraci system rc error kod */
static int bench(void)
{
	int i,j,k;	
	pid_t pid=0;
	FILE *f;

  /* check avaibility of target server */
  //调用socket.c代码，建立一次TCP连接
	i=Socket(proxyhost==NULL?host:proxyhost,proxyport);
	if(i<0)
	{ 
		fprintf(stderr,"\nConnect to server failed. Aborting benchmark.\n");
        return 1;
	}

	//why close i?
	close(i);
	/* create pipe */
	if(pipe(mypipe))
	{
		perror("pipe failed.");
		return 3;
	}

	/* not needed, since we have alarm() in childrens */
	 /* wait 4 next system clock tick */
	 /*
	 cas=time(NULL);
	 while(time(NULL)==cas)
	      sched_yield();
	 */

	 /* fork childs */
	//fork出clients个子进程
	for(i=0;i<clients;i++)
	{
		pid=fork();
	    if(pid <= (pid_t) 0)
		{
		   /* child process or error*/
			sleep(1); /* make childs faster */
			break;
		}
	}

	if( pid< (pid_t) 0)
	{
		fprintf(stderr,"problems forking worker no. %d\n",i);
		perror("fork failed.");
		return 3;
	}

	if(pid== (pid_t) 0)
	{
		/* I am a child */
		if(proxyhost==NULL)
			benchcore(host,proxyport,request);
		else
			benchcore(proxyhost,proxyport,request);

		/* write results to pipe */
		//子进程把测试结果输出到管道
		f=fdopen(mypipe[1],"w");
		if(f==NULL)
		{
			perror("open pipe for writing failed.");
			return 3;
		}
		/* fprintf(stderr,"Child - %d %d\n",speed,failed); */
		fprintf(f,"%d %d %d\n",speed,failed,bytes);
		fclose(f);
		return 0;
	} 
	else//如果是父进程，从管道读出数据，并汇总数据信息
	{
		f=fdopen(mypipe[0],"r");
		if(f==NULL) 
		{
			perror("open pipe for reading failed.");
			return 3;
		}
		//设置缓冲区，_IONBF表示没有缓存
		setvbuf(f,NULL,_IONBF,0);
		speed=0;
        failed=0;
        bytes=0;

		while(1)
		{
			pid=fscanf(f,"%d %d %d",&i,&j,&k);
			if(pid<2)
			{
				fprintf(stderr,"Some of our childrens died.\n");
				break;
			}
			speed+=i;
			failed+=j;
			bytes+=k;
			/* fprintf(stderr,"*Knock* %d %d read=%d\n",speed,failed,pid); */
			//记录读了多少个子进程的数据，读完就退出
			if(--clients==0)
				break;
		}
		fclose(f);

	  //将结果打印在屏幕上
		printf("\nSpeed=%d pages/min, %d bytes/sec.\nRequests: %d susceed, %d failed.\n",\
			(int)((speed+failed)/(benchtime/60.0f)),\
			(int)(bytes/(float)benchtime),speed,failed);
	}
	return i;
}

void benchcore(const char *host,const int port,const char *req)
{
	int rlen;
	char buf[1500];//保存服务器的响应报文
	int s,i;
	struct sigaction sa;

	/* setup alarm signal handler 注册SIGARALM信号的信号处理函数*/
	sa.sa_handler=alarm_handler;
	sa.sa_flags=0;
	if(sigaction(SIGALRM,&sa,NULL))
		exit(3);
	alarm(benchtime);	//设置闹钟，超时发送SIGARALM信号

	rlen=strlen(req);	//计算请求报文的长度
nexttry:while(1)
		{
			if(timerexpired)//一旦超时，则返回
			{
				if(failed>0)
				{
				/* fprintf(stderr,"Correcting failed by signal\n"); */
					failed--;
				}
				return;
			}

			s=Socket(host,port);                          
			if(s<0)
			{ 
				failed++;
				continue;
			} 
		//向服务器发出请求
			if(rlen!=write(s,req,rlen))
			{
				failed++;
				close(s);
				continue;
			}
			if(http10==0) //针对http0.9做的特殊处理
				if(shutdown(s,1)) //调用shutdown函数使客户端不能呢向服务器发送请求，成功-->0，失败-->-1
				{ 
					failed++;
					close(s);
					continue;
				}

				if(force==0) //force==0 等待从server返回的数据
				{
				/* read all available data from socket */
					while(1)
					{
						if(timerexpired) 
							break; 
						i=read(s,buf,1500);//读取从服务器返回的数据，保存到buf中
				/* fprintf(stderr,"%d\n",i); */
						if(i<0) 
						{ 
							failed++;
							close(s);
							goto nexttry;
						}
						else
							if(i==0) 
								break;
							else
								bytes+=i;
					}
				}
				if(close(s)) 
				{
					failed++;
					continue;
				}
				speed++;
		}
}
