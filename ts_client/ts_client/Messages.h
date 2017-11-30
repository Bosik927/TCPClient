#pragma once
#include "TCPSocket.h"

bool is_number(std::string& s);
void requestID(TCPSocket &Socket);
void sendL(TCPSocket &Socket, std::string &id);
void trial(TCPSocket &Socket, std::string &id);
void disconnection(TCPSocket &Socket, std::string &id);
