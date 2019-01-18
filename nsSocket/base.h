#pragma once
#include "stdafx.h"
#include<winsock2.h>
#include<windows.h>
#include<string>
#include<stdio.h>

#pragma comment (lib , "Ws2_32.lib")

class Socket {
public : 
	Socket(void);
	Socket(char * , int , int);
	virtual ~Socket();
	int startWSA();
	int initializeSocket();
	void closeSocket(SOCKET sock);

protected : 
	SOCKET m_sock; 
	struct sockaddr_in m_sockAddr;

private:
	char *m_address; 
	int m_port; 
	int m_protocol; 
};

