#include "TCPSocket.h"
#include <system_error>

TCPSocket::TCPSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
}
TCPSocket::~TCPSocket() {
	closesocket(sock);
}
void TCPSocket::connection(std::string &IPAddress, unsigned int port) const {
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IPAddress.c_str(), &hint.sin_addr);

	const int  connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == INVALID_SOCKET) {
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error connection socket");
	}
}
void TCPSocket::Send(const std::string &message) {
	int ret = send(sock, message.c_str(), message.size(), 0);
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}
void TCPSocket::Recv(char buf[], unsigned bufLeng) {
	int bytesReceived = recv(sock, buf, bufLeng, 0);
}