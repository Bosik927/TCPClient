#pragma once
#include <string>

struct packet {
private:
	std::string id;
	std::string operation;
	std::string time;
	std::string answer;
public:
	packet(const std::string &id_, const std::string &op_, const std::string &ans_, const std::string &tim_);
	packet(const std::string& rawData);

	std::string getID();
	std::string getOperation();
	std::string getTime();
	std::string getAnswer();
	std::string convertToString();
	void display();
};
