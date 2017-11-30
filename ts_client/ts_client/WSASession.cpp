#include "WSASession.h"

WSASession::WSASession() {
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret != 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
}
WSASession::~WSASession() {
	WSACleanup();
}