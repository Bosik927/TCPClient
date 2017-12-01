#include "Messages.h"
#include <iostream>
#include "Packet.h"
#include <cctype>
#include <algorithm>
#include "CurrentTime.h"

bool is_number(std::string& s) {
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
void requestID(TCPSocket &Socket) {
	packet messagePakiet("0", "GEN", "00", currentTime());
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}
void sendL(TCPSocket &Socket, std::string &id) {
	std::string numberL; unsigned int division = 1;
	while (true) {
		std::cout << "Podaj dodatnia parzysta liczbe L (mniejsza niz 100): ";
		std::getline(std::cin, numberL);
		
		if (is_number(numberL)) division = std::stoi(numberL);
		if (division < 100) {
			if (is_number(numberL) & division % 2 == 0) break;

			std::cout << "Sprobuj jeszcze raz! Niepoprawna liczba" << std::endl;
		}
		else
		{
			std::cout << "Sprobuj jeszcze raz! Podana liczba jest wieksza od 100!" << std::endl;
		}
	}
	packet messagePakiet(id, "NUM", numberL, currentTime());
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}
void trial(TCPSocket &Socket, std::string &id) {

	std::string numberToSend = "a";
	std::cout << "Sprobuj zgadnac liczbe (miedzy 0 a 100): ";
	while (true) {

		getline(std::cin, numberToSend);

		if (is_number(numberToSend))
		{	unsigned int numberToSendInt = std::stoi(numberToSend);
		
		if (0<numberToSendInt < 100) { break; }
		else std::cout << "Podano wieksza liczbe niz 100! ";
		}

		std::cout << "Podano nieliczbe! Sprobuj jeszcze raz!" << std::endl;
	}
	packet messagePakiet(id, "ATT", numberToSend, currentTime());
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);
}
void disconnection(TCPSocket &Socket, std::string &id) {
	packet messagePakiet(id, "EXIT", "0", currentTime());
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}