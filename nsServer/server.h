#pragma once

#include "../nsSocket/base.h"

class Server : public Socket {

public:
	Server(char *, int, int); 
	~Server(); 
	int bindSocket();
	int startListen();
	int startAccept();
	int receive(char *);

private : 
	SOCKET m_acceptSocket;

};