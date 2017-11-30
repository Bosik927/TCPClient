#include "Packet.h"
#include <iostream>
#include <regex>

packet::packet(const std::string &id_, const std::string &op_, const std::string &ans_, const std::string &tim_) {
	this->id = id_;
	this->operation = op_;
	this->answer = ans_;
	this->time = tim_;
}
packet::packet(const std::string& rawData) {

	std::string message = rawData;
	std::regex reg("[0-9a-zA-Z:\. _]+(?=\\/)");
	std::smatch match;

	std::regex_search(message, match, reg);
	id = match[0];
	message = match.suffix();

	std::regex_search(message, match, reg);
	operation = match[0];
	message = match.suffix();

	std::regex_search(message, match, reg);
	time = match[0];
	message = match.suffix();

	std::regex_search(message, match, reg);
	answer = match[0];
	message = match.suffix();
}
std::string packet::getID() { return id; }
std::string packet::getOperation() { return operation; }
std::string packet::getTime() { return time; }
std::string packet::getAnswer() { return answer; }
std::string packet::convertToString() {
	return ("Id#" + id + "/Op#" + operation + "/Time#" + time + "/Odp#" + answer + "/");
}
void packet::display()
{
	std::cout << "ID: " << id << " OPERATION: " << operation << " TIME: " << time << " ANSWER: " << answer << std::endl;
}