/*************************************************************************
	> File Name: udpServer.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Sat 22 Apr 2017 11:01:53 PM PDT
 ************************************************************************/
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet.h>
#include<apar/inet.h>
#include<string>

using namespace std;

class udpServer
{
	public:
		udpServer();
		~udpServer();
		initServer();
		const int& sendData(const std::string& instring,struct sockaddr_in &remote, socklen_t &len);
		const int& recvData(const std::string& outstring);
		const int&brocast();
	private:
		udpServer(const udpServer&);
		udpServer operator=(const udpServer&);
	private:
		int _sock;
		std::string _ip;
		int port;
		map<string,struct sockaddr_in> user_list;
};

#endif
