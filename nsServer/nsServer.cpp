// nsServer.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "server.h"

#pragma comment (lib , "Ws2_32.lib")

#define LOOPBACK_ADDRESSS "127.0.0.1"
#define TEST_PORT 27015
#define IP_PROTOCOL 6

Server::Server(char *address, int port, int ipProtocol) : Socket( address , port , ipProtocol ) , m_acceptSocket(-1)
{
}

Server::~Server()
{
	closeSocket(m_acceptSocket);
}

int Server::bindSocket()
{
	if (bind(m_sock , (struct sockaddr *)&m_sockAddr, sizeof(m_sockAddr)) == SOCKET_ERROR) {
		wprintf(L"Socket Error while Binding : %d\n", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Server::startListen()
{
	int result = listen(m_sock, 3);
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Listen error : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Server::startAccept()
{
	int c = sizeof(struct sockaddr);
	int result = 1;
	m_acceptSocket = accept(m_sock, NULL, NULL);
	if (m_acceptSocket == INVALID_SOCKET) {
		wprintf(L"Socket Error : %d\n", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Server::receive(char *buffer)
{
	int result = recv(m_acceptSocket, buffer, sizeof(buffer), 0);
	return result;
}


int main()
{
	Server server(LOOPBACK_ADDRESSS, TEST_PORT, IP_PROTOCOL);
	if (server.startWSA() == 1) {
		return 1;
	}
	if (server.initializeSocket() == 1) {
		return 1;
	}
	if (server.bindSocket() == 1) {
		return 1;
	}
	if (server.startListen() == 1) {
		return 1;
	}
	if (server.startAccept() == 1) {
		return 1;
	}
	int result; 
	int i = 1; 
	char buffer[1024] = "";
	char *message = ""; 
	do {
		result = server.receive(buffer);
		if (result > 0) {
			printf("%s", buffer);
		} else if (result == 0) {
			wprintf(L"\nClosing Connection...");
		} else {
			wprintf(L"Receive Failed with error : %d", WSAGetLastError());
			return WSAGetLastError();
		}
	} while (result > 0); 
	::Sleep(4000); 
    return 0;
}

