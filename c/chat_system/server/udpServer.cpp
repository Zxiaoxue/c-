/*************************************************************************
	> File Name: udpServer.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 22 Apr 2017 11:01:25 PM PDT
 ************************************************************************/
#include "udpServer.h"

using namespace std;

udpServer::udpServer(std::string& ip, int port)
	:_ip(ip)
	,_port(port)
{}

void initServer()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		printf_log("socket failed!\n",FATAL);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip.c_str());

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		printf_log("bind failed!\n", FATAL);
		exit(2);
	}

}

const int& udpServer::sendData(const std::string& instring,struct sockaddr_in &remote, socklen_t &len)
{
		size_t s = sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote, len);

		if(s < 0)
		{
			printf_log();
		}

		putData(instring);
		return s;
}

const int& udpServer::recvData(const std::string& outstring)
{
	char buf[SIZE];
	struct sozkaddr_in remote;
	socklen_t len = sizeof(remote);
	size_t s =  recvfrom(sock, buf, sizeof(buf), 0,(struct sockaddr*)&remote, &len);

	if(s < 0)
	{
		printf_log();
	}

	outstring = buf;
	getData(outstring);
	return s;
}

const int& udpServer::brocast()
{

}

udpServer::~udpServer()
{
	close(sock);
}
