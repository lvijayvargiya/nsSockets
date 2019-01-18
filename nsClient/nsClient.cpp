// nsClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "client.h"

#pragma comment (lib , "Ws2_32.lib")

#define LOOPBACK_ADDRESSS "127.0.0.1"
#define TEST_PORT 27015
#define IP_PROTOCOL 6

Client::Client(char *address, int port, int ipProtocol) : Socket(address , port , ipProtocol)
{
}

Client::~Client()
{
	closeSocket(m_sock);
	WSACleanup(); 
}

int Client::connectSocket()
{
	int result = connect(m_sock, (SOCKADDR *)&m_sockAddr, sizeof(m_sockAddr));
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Error : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

int Client::sendData(char *message)
{
	long result = send(m_sock, message, (int)strlen(message), 0);
	if (result == SOCKET_ERROR) {
		wprintf(L"Socket Error while Sending : %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}


int main()
{
	Client c(LOOPBACK_ADDRESSS, TEST_PORT, IP_PROTOCOL);

	if (c.startWSA() == 1) {
		return 1;
	}

	if (c.initializeSocket() == 1) {
		return 1; 
	}

	if (c.connectSocket() == 1) {
		return 1;
	}
	char message[1024];
	scanf("%[^\n]s", &message);
	if (c.sendData(message) != 0) {
		return 1;
	}
	::Sleep(3000); 
    return 0;
}

