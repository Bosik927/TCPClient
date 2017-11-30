#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <WS2tcpip.h>
#include <regex>
#include "WSASession.h"
#include "TCPSocket.h"
#include "Packet.h"
#include "Messages.h"

#pragma comment (lib,"ws2_32.lib")

//generate id,			->GEN answer in id
//send num L			->NUM answer in answer
//send trials			->ATT answer in answer
//send result			->TRY answer in answer
//answer for result		->ANS answer in answer
//disconnection			->EXI  
// Example:
// id#01/|op#GEN/time#12:00:00.000/odp#123123/

/// Do zrobinia:
/// - znacznik czasu
int main() {
	std::string ipAddress = "127.0.0.1";
	const unsigned int port = 19975;

	WSASession Session;
	TCPSocket Socket;

	Socket.connection(ipAddress, 19975);

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


	while(numOfTrielsInt) {
		std::cout << "Twoja aktualna liczba prob to: " << numOfTrielsInt << std::endl;
		trial(Socket, ID);

		Socket.Recv(buf, bufLeng);
		packet receivedPacket2(buf);
		if(receivedPacket2.getAnswer() == "game_over") {
			std::cout << "Przegrales!" << std::endl; break;
		}
		if(receivedPacket2.getAnswer() == "win") {
			std::cout << "Wygrales!" << std::endl; break;
		}
		if(receivedPacket2.getAnswer() == "bad" &&numOfTrielsInt > 0) {
			std::cout << "Sprobuj jeszcze raz!" << std::endl; numOfTrielsInt--;
		}

	}

	//disconnection(Socket, ID);

	std::cin.ignore(1);

	return 0;
}
