#include "Messages.h"
#include <iostream>
#include "Packet.h"
#include <cctype>
#include <algorithm>

bool is_number(std::string& s) {
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
void requestID(TCPSocket &Socket) {
	packet messagePakiet("0", "GEN", "00", "12:00:00.000");
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}
void sendL(TCPSocket &Socket, std::string &id) {
	std::string numberL; unsigned int division = 1;
	while (true) {
		std::cout << "Podaj dodatnia parzysta liczbe L: ";
		std::getline(std::cin, numberL);
		if (is_number(numberL)) division = std::stoi(numberL);

		if (is_number(numberL) & division % 2 == 0) break;

		std::cout << "Sprobuj jeszcze raz!" << std::endl;
	}
	packet messagePakiet(id, "NUM", numberL, "12:00:00.000");
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}
void trial(TCPSocket &Socket, std::string &id) {

	std::string numberToSend = "a";
	std::cout << "Sprobuj zgadnac liczbe: ";
	while (true) {

		getline(std::cin, numberToSend);

		if (is_number(numberToSend)) { break; }

		std::cout << "Podano nieliczbe! Sprobuj jeszcze raz!" << std::endl;
	}
	packet messagePakiet(id, "ATT", numberToSend, "12:00:00.000");
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);
}
void disconnection(TCPSocket &Socket, std::string &id) {
	packet messagePakiet(id, "EXIT", "0", "12:00:00.000");
	std::string messageString = messagePakiet.convertToString();
	Socket.Send(messageString);

}