// nsSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "base.h"

#pragma comment (lib , "Ws2_32.lib")

Socket::Socket(char * address, int port, int protocol) : m_address(address), m_port(port), m_protocol(protocol), m_sock1(-1), m_sock2(-1)
{
}

Socket::~Socket()
{
	closeSocket();
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
	m_socket.sin_family = AF_INET;
	if (m_address == NULL) {
		return 1;
	}
	m_socket.sin_addr.s_addr = inet_addr(m_address);
	m_socket.sin_port = htons(m_port);
	if (m_protocol == 6) {
		m_sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	} else if (m_protocol == 17) {
		m_sock1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
	if (m_sock1 == INVALID_SOCKET) {
		wprintf(L"Socket Creation Failed\n");
		return 1;
	}
	return 0;
}

int Socket::bindSocket()
{
	if (bind(m_sock1, (struct sockaddr *)&m_socket, sizeof(m_socket)) == SOCKET_ERROR) {
		wprintf(L"Socket Error while Binding : %d\n", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Socket::connectSocket() {
	int result = connect(m_sock1, (SOCKADDR *)&m_socket, sizeof(m_socket));
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Error : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Socket::startListen()
{
	int result = listen(m_sock1, 3);
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Listen error : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Socket::startAccept()
{
	int c = sizeof(struct sockaddr);
	int result = 1;
	m_sock2 = accept(m_sock1, NULL, NULL);
	if (m_sock2 == INVALID_SOCKET) {
		wprintf(L"Socket Error : %d\n", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Socket::receive(char *buffer)
{
	int result = recv(m_sock2, buffer, sizeof(buffer), 0);
	return result;
}

int Socket::sendData(char *message)
{
	long result = send(m_sock1, message, (int)strlen(message), 0);
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Error while Sending : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

void Socket::closeSocket()
{
	if (m_sock1 != -1) {
		closesocket(m_sock1);
	}
	if (m_sock2 != -1) {
		closesocket(m_sock2);
	}
}


