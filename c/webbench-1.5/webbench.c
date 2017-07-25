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
volatile int timerexpired=0;//�ж�ѹ����ʱ���Ƿ��Ѿ��ﵽ�趨ʱ��
int speed=0;//���̳ɹ��õ���������Ӧ������
int failed=0;//ʧ�ܵ�����(speed����ɹ���failed����ʧ��)
int bytes=0;//���̳ɹ��ӷ�������ȡ���ֽ���

/* globals */
int http10=1; /* http�汾��0����http/0.9, 1����http/1.0, 2����http/1.1 */

/*���󷽷���GET, HEAD, OPTIONS, TRACE */

int method=METHOD_GET;//Ĭ��ΪGET����
int clients=1;		//��������Ŀͻ�����Ŀ��Ĭ��Ϊ1������ͨ��-c/-clientѡ������
int force=0;			//�Ƿ���Ҫ�ȴ���ȡ��server���ص����ݣ�0��ʾ�ȴ���ȡ
int force_reload=0;	//�Ƿ�ʹ�û��棬1��ʾ�����棬0��ʾ����-----�Ƿ���������
int proxyport=80;		//����������˿ں�
char *proxyhost=NULL;//���������IP����ʼ��ΪNULL
int benchtime=30;		//ѹ��ʱ�䣬Ĭ��Ϊ30�룬����ͨ��-t/-timeѡ������

/* internal */
int mypipe[2];
char host[MAXHOSTNAMELEN];	//��������ip
char request[REQUEST_SIZE];	//���������ģ�(�����У�����ͷ�����У���������)

/*
struct option {
	const char *name;
	int has_arg;
    int *flag;
    int val;
};
struct option�ṹ����Ԫ�ؽ������£�
1.const char *name;	//ѡ����

2.int has_arg;		//������ѡ���Ƿ���ѡ�����
has_arg��3��ֵ��
���ų���			 ��ֵ			����
no_argument		  0		��ʾ��ѡ����治������ֵ��
required_argument  1		��ʾ��ѡ�����һ��������ֵ��		
optional_argument  2		��ʾ��ѡ�������Ը���Ҳ���Բ�������ֵ

3.int* flag;			//����������getopt_long()�ķ���ֵ������ʲô��
���flagΪNULL�������᷵�������optionƥ���valֵ��
���flag����NULL����valֵ����flag��ָ����ڴ棬���ҷ���0

4.int val;			//���flagΪNULL����ôvalͨ���Ǹ��ַ�������
�����ѡ���볤ѡ��һ�£���ô���ַ���Ӧ����optstring�г��ֵ����ѡ��Ĳ�����ͬ
*/

//struct option�ṹ���ʼ��
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

/*�źŴ�������������ʱ�����ʱ����SIGALARM�źţ������ô˺�������timerexpried��Ϊ1����ʾ�ӽ�����Ҫ�˳�
�ں���ĺ�������ʱ�ῴ�����ڳ����whileѭ���л᲻�ϼ���ֵ��ֻ��timerexpiredΪ1ʱ������Ż�����whileѭ��
������*/
static void alarm_handler(int signal)
{
   timerexpired=1;//timerexpired:�ж�ѹ��ʱ���Ƿ��Ѿ��ﵽ�趨ʱ��
}	

/*
usage������webbench�÷�����
	-f|--force               ����Ҫ�ȴ���������Ӧ
	-r|--reload              �������¼�������
	-t|--time <sec>          ���ж೤ʱ�䣬��λ����
	-p|--proxy <server:port> ʹ�ô����������������
	-c|--clients <n>         �������ٸ��ͻ���
	-9|--http09              ʹ��HTTP/0.9
	-1|--http10              ʹ��HTTP/1.0Э��
	-2|--http11              ʹ��HTTP/1.1Э��
	--get                    ʹ��GET��������
	--head                   ʹ��HEAD��������
	--options                ʹ��OPTIONS��������
	--trace                  ʹ��TRACE��������
	-?|-h|--help             ��ӡ������Ϣ
	-V|--version			   ��ʾ�汾��

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

 /*getopt_long����
�������ܣ��������������в���������argc��argv�ֱ����������������ݣ���main������������в���һ��
int getopt_long(int argc, char* argv[], const char* optstring, const struct option* longopts, int* longindex);
����optstring��Ϊѡ���ַ���������getopt���Դ����Ǹ�ѡ���Լ��ĸ�ѡ����Ҫ���������ѡ���ַ��������ĸ����ð��: ":"��
���ʾ������صĲ�����ȫ�ֱ���optarg����ָ��˶������������ڴ����ڼ������˲�����optstringָ��������ѡ�
getopt������ʾһ��������Ϣ������ȫ�ֱ�������Ϊ"?"�ַ���ȫ�ֱ�������Ϊ0�򲻻��ӡ������Ϣ��
����ֵ��ÿ�ε��øú��������������һ��ѡ����ҷ������Ķ�ѡ����������ϣ���û��ѡ���ˣ���᷵��-1
*/
	while((opt=getopt_long(argc,argv,"912Vfrt:p:c:?h",long_options,&options_index))!=EOF )
	{
	 /*
	 #include<unistd.h>
	 extern char* optarg;//ѡ��Ĳ���ָ��
	 extern int optind;  //��һ�ε���getopt_longʱ����optind�洢��λ�ô����¿�ʼ���ѡ��
	 extern int opterr;  //��opterr=0ʱ��getopt_long����stderr���������Ϣ
	 extern int optopt;  //��������ѡ���ַ���������optstring�л�ȱ�ٱ�Ҫ����ʱ����ѡ��洢��optopt�У�
						 getopt_long����'?'*/
		switch(opt)
		{
		case  0 : break;
		case 'f': force=1;break;
		case 'r': force_reload=1;break; 
		case '9': http10=0;break;
		case '1': http10=1;break;
		case '2': http10=2;break;
		case 'V': printf(PROGRAM_VERSION"\n");exit(0);
		case 't': benchtime=atoi(optarg);break;	     //optarg��ѡ��Ĳ���ָ�룬-tѡ������������ʱ��
		case 'p': //�����ַ�'p'��˵��ʹ�ô��������
	     /* proxy server parsing server:port */
		 /*���������������IP:Port  eg: 192.168.237.128:8080  */
			tmp=strrchr(optarg,':');//tmp = ":8080"
			proxyhost=optarg;
			if(tmp==NULL)
			{
				break;
			}
			if(tmp==optarg)//tmp == ":8080" == optorg û������IP,ֻ�ж˿ں�
			{
				fprintf(stderr,"Error in option --proxy %s: Missing hostname.\n",optarg);
				return 2;
			}
			if(tmp==optarg+strlen(optarg)-1)//org == "192.168.237.128:" == tmp, û�д���������˿ں�
			{
				fprintf(stderr,"Error in option --proxy %s Port number is missing.\n",optarg);
				return 2;
			}
			*tmp='\0';//������� tmp = ":8080" tmp+1 = "8080"
			proxyport=atoi(tmp+1);
			break;
		case ':':
		case 'h':
		case '?': usage();return 2;break;//getopt_long�ڷ���ѡ��ʱ������һ��û�ж������ѡ��򷵻�ֵΪ'?'
		case 'c': clients=atoi(optarg);break; //��ʱ��optargָ��Ĳ�����Ϣ�ǿͻ�����Ŀ
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

	build_request(argv[optind]);//argv[optind]=URL,��������ͷ
 /* print bench info */
 //��ӡ���Ե������Ϣ
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

 //���Ĵ���
	return bench();
}

//��������ͷ
void build_request(const char *url)
{
	char tmp[10];
	int i;

  /*int bzero(void* s, size_t n);���ڴ��(�ַ���s)�е�ǰn���ֽ���Ϊ0������'\0'*/
	bzero(host,MAXHOSTNAMELEN);
	bzero(request,REQUEST_SIZE);

  //����http�汾��Ϣ
	if(force_reload && proxyhost!=NULL && http10<1) http10=1;
	if(method==METHOD_HEAD && http10<1) http10=1;
	if(method==METHOD_OPTIONS && http10<2) http10=2;
	if(method==METHOD_TRACE && http10<2) http10=2;

  //������󷽷�
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
  // eg: url = "http://www.baidu.com/" --- i = 4-0+3 = 7 ��ʱiָ���һ��w��λ��
		i=strstr(url,"://")-url+3;

  /* printf("%d\n",i); */
  //��ʱurl+i = "www.baidu.com/", Ѱ��'/'�Ƿ���url+i���Ӵ�����Ϊ������������'/'��β
		if(strchr(url+i,'/')==NULL) 
		{
			fprintf(stderr,"\nInvalid URL syntax - hostname don't ends with '/'.\n");
			exit(2);
		}
		if(proxyhost==NULL)//û�д�������
		{
		/* get port from hostname */
		/* index(s, c)��������c��s�е�һ�γ��ֵ�λ��*/
			if(index(url+i,':')!=NULL && index(url+i,':')<index(url+i,'/'))//�д��������˿ں�
			{
				//eg��http://www.baidu.com/:8080  strchr(str��val)�����ַ���str���״γ���val��λ�� 
				//��url+iλ�ÿ�ʼ��21-0-7=14���ַ���ֵ��host host=www.baidu.com/
				strncpy(host,url+i,strchr(url+i,':')-url-i);
				//���tmp��ǰ10���ֽ�λ��	 
				bzero(tmp,10);
				//���˿ںŷŵ�tmp��ȥ
				strncpy(tmp,index(url+i,':')+1,strchr(url+i,'/')-index(url+i,':')-1);
				/* printf("tmp=%s\n",tmp); */
				proxyport=atoi(tmp);	//���˿ںŸ�ֵ��roxyport
				if(proxyport==0) proxyport=80;
			} 
			else//û�ж˿ں� eg: http://www.baidu.com/
			{
				strncpy(host,url+i,strcspn(url+i,"/"));
			}
			// printf("Host=%s\n",host);
			//#############################################
			//why here using request+strlen(request)?
			strcat(request+strlen(request),url+i+strcspn(url+i,"/"));
		} 
		else //�д�������
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
		//���Connection:close����Ϊ�����ӣ�һ�����Ӽ�ʱ�ر�
		if(http10>1)
			strcat(request,"Connection: close\r\n");
		/* add empty line at end */
		//��ӿ���
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
  //����socket.c���룬����һ��TCP����
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
	//fork��clients���ӽ���
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
		//�ӽ��̰Ѳ��Խ��������ܵ�
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
	else//����Ǹ����̣��ӹܵ��������ݣ�������������Ϣ
	{
		f=fdopen(mypipe[0],"r");
		if(f==NULL) 
		{
			perror("open pipe for reading failed.");
			return 3;
		}
		//���û�������_IONBF��ʾû�л���
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
			//��¼���˶��ٸ��ӽ��̵����ݣ�������˳�
			if(--clients==0)
				break;
		}
		fclose(f);

	  //�������ӡ����Ļ��
		printf("\nSpeed=%d pages/min, %d bytes/sec.\nRequests: %d susceed, %d failed.\n",\
			(int)((speed+failed)/(benchtime/60.0f)),\
			(int)(bytes/(float)benchtime),speed,failed);
	}
	return i;
}

void benchcore(const char *host,const int port,const char *req)
{
	int rlen;
	char buf[1500];//�������������Ӧ����
	int s,i;
	struct sigaction sa;

	/* setup alarm signal handler ע��SIGARALM�źŵ��źŴ�����*/
	sa.sa_handler=alarm_handler;
	sa.sa_flags=0;
	if(sigaction(SIGALRM,&sa,NULL))
		exit(3);
	alarm(benchtime);	//�������ӣ���ʱ����SIGARALM�ź�

	rlen=strlen(req);	//���������ĵĳ���
nexttry:while(1)
		{
			if(timerexpired)//һ����ʱ���򷵻�
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
		//���������������
			if(rlen!=write(s,req,rlen))
			{
				failed++;
				close(s);
				continue;
			}
			if(http10==0) //���http0.9�������⴦��
				if(shutdown(s,1)) //����shutdown����ʹ�ͻ��˲�������������������󣬳ɹ�-->0��ʧ��-->-1
				{ 
					failed++;
					close(s);
					continue;
				}

				if(force==0) //force==0 �ȴ���server���ص�����
				{
				/* read all available data from socket */
					while(1)
					{
						if(timerexpired) 
							break; 
						i=read(s,buf,1500);//��ȡ�ӷ��������ص����ݣ����浽buf��
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
