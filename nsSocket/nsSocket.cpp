// nsSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "base.h"

#pragma comment (lib , "Ws2_32.lib")

Socket::Socket(void)
{
}

Socket::Socket(char * address, int port, int protocol) : m_address(address), m_port(port), m_protocol(protocol) , m_sock(-1) 
{
}

Socket::~Socket() 
{
	closeSocket(m_sock); 
	WSACleanup();
}

int Socket::startWSA() {
	WSAData wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 1;
	}
	return 0;
}

int Socket::initializeSocket()
{
	m_sockAddr.sin_family = AF_INET;
	if (m_address == NULL) {
		return 1;
	}
	m_sockAddr.sin_addr.s_addr = inet_addr(m_address);
	m_sockAddr.sin_port = htons(m_port);
	if (m_protocol == 6) {
		m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	} else if (m_protocol == 17) {
		m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
	if (m_sock == INVALID_SOCKET) {
		wprintf(L"Socket Creation Failed\n");
		return 1;
	}
	return 0;
}                                                                              

void Socket::closeSocket(SOCKET sock)
{
	if (sock != -1) {
		closesocket(sock); 
	}
}




