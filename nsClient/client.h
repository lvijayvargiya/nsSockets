#pragma once

#include "stdafx.h"
#include "../nsSocket/base.h"

class Client : public Socket {
public :
	Client(char *, int, int); 
	~Client(); 
	int connectSocket(); 
	int sendData(char *); 
};