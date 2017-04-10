/*************************************************************************
	> File Name: cgi_math.c
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sun 09 Apr 2017 06:15:27 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#define SIZE 4096


//data1=100&data2=200
static math_data(const char* data)
{
	printf("math_data is runing!\n");
	char* arr[3];
	int i = 0;
	char* start = data;
	assert(data);

	while(*start)
	{
		if(*start == '=')
		{
			arr[i] = start+1;
			i++;
		}
		else if(*start == '&')
		{
			*start='\0';
		}

		start++;
	}
	arr[i] = NULL;

	int data1 = atoi(arr[0]);
	int data2 = atoi(arr[1]);
	int data3 = data1+data2;
	printf("data1: %d + data2: %d = %d\n", data1, data2, data3);
} 


int main()
{
	char method[SIZE];
	char query_string[SIZE];
	char content_len[SIZE];
	char content_data[SIZE];

	memset(method,'\0', sizeof(method)-1);
	memset(query_string,'\0', sizeof(query_string)-1);
	memset(content_len,'\0', sizeof(content_len)-1);
	memset(content_data,'\0', sizeof(content_data)-1);

	if(getenv("METHOD") != NULL)
	{
		strcpy(method, getenv("METHOD"));
	}
	else
	{
		printf("METHOD is not found!\n");
		return 1;
	}

	if(strcasecmp(method, "GET") == 0)
	{
		if(getenv("QUERY_STRING") != NULL)
		{
			strcpy(content_data, getenv("QUERY_STRING"));
		}
		else
		{
			printf("QUERY_STRING is not found!\n");
			return 2;
		}
	}
	else
	{
		if(getenv("CONTENT_LENGTH"))
		{
			strcpy(content_len,getenv("CONTENT_LENGTH"));

			printf("content_len:%s\n", content_len);
			printf("CONTENT_LENGTH:%s\n", getenv("CONTENT_LENGTH"));
			int len = atoi(content_len);
			printf("len:%d\n", len);
			int i = 0;
			char ch = '\0';
			for(; i<len; i++)
			{
				ssize_t _s = read(0, &ch, 1);
				if(_s < 0)
				{
					printf("read failed!\n");
					return 4;
				}
				printf("ch:%c\n", ch);
				content_data[i] = ch;
			}
			content_data[i] = '\0';
			printf("content_data:%s\n", content_data);
		}
		else
		{
			printf("CONTENT_LENGTH is not found!\n");
			return 3;
		}
	}
	printf("cgi echo:%s\n", content_data);
	printf("method:%s\n", method);
	printf("content_len:%d\n", content_len);
	printf("query_string:%s\n", query_string);

	math_data(content_data);
	return 0;
}
