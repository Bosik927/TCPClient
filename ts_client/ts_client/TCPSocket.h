#pragma once
#include <WS2tcpip.h>
#include <string>

class TCPSocket {
protected:
	SOCKET sock;
public:
	TCPSocket(); 
	~TCPSocket();
	void connection(std::string &IPAddress, unsigned port) const;
	void Send(const std::string &message); 
	void Recv(char buf[], unsigned bufLeng);
};
