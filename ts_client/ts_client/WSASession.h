#pragma once
#include <WS2tcpip.h>
#include <system_error>

class WSASession {
private:
	WSAData data;
public:
	WSASession();
	~WSASession();
};
