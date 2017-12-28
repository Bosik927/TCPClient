#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <WS2tcpip.h>
#include <regex>
#include <chrono>
#include <Windows.h>
#include <iomanip>
#include "WSASession.h"
#include "TCPSocket.h"
#include "Packet.h"
#include "Messages.h"
#include "CurrentTime.h"

#pragma comment (lib,"ws2_32.lib")

int main() {

	std::string ipAddress = "127.0.0.1";
	const unsigned int port = 19975;
	WSASession Session;
	TCPSocket Socket;

	Socket.connection(ipAddress, port);

	requestID(Socket);
	char buf[64]; const unsigned int bufLeng = 64;
	Socket.Recv(buf, bufLeng);
	std::string ID;
	{
		packet receivedPacket(buf);
		ID = receivedPacket.getID();
	}
	std::cout << ID << std::endl;
	sendL(Socket, ID);

	Socket.Recv(buf, bufLeng);
	packet receivedPacket(buf);
	std::string numOfTriels = receivedPacket.getAnswer();
	unsigned int numOfTrielsInt = std::stoi(numOfTriels);
	std::cout << "Twoja liczba prob to: " << numOfTrielsInt << std::endl;

	while (numOfTrielsInt) {
		std::cout << "Twoja aktualna liczba prob to: " << numOfTrielsInt << std::endl;
		trial(Socket, ID);

		Socket.Recv(buf, bufLeng);
		packet receivedPacket2(buf);
		if (receivedPacket2.getAnswer() == "game_over") {
			std::cout << "Przegrales!" << std::endl; break;
		}
		if (receivedPacket2.getAnswer() == "win") {
			std::cout << "Wygrales!" << std::endl; break;
		}
		if (receivedPacket2.getAnswer() == "bad" &&numOfTrielsInt > 0) {
			std::cout << "Sprobuj jeszcze raz!" << std::endl; numOfTrielsInt--;
		}
		std::cin.ignore(1);
	}
	return 0;
}
