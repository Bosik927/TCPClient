#include <iostream>
#include <string>
#include <ctime>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")


class WSASession {
private:
	WSAData data;
public:
	WSASession() {
		int ret = WSAStartup(MAKEWORD(2, 2), &data);
		if (ret != 0)
			throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
	}

	~WSASession() {
		WSACleanup();
	}

};
class TCPSocket
{
protected:
	SOCKET sock;

public:
	// TWORZENIE SOCKETA
	TCPSocket()
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
			throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
	}

	// DESTRUKTOR SOCKETU USUWANIE SOCKETA
	~TCPSocket() {
		closesocket(sock);
	}

	//	POLACZENIE Z SERWEREM
	void connection(const std::string &IPAddress, const unsigned int port) const
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, IPAddress.c_str(), &hint.sin_addr);

		const int  connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == INVALID_SOCKET)
		{
			throw std::system_error(WSAGetLastError(), std::system_category(), "Error connection socket");
		}
	}
	
	//WYSYLANIE PAKIETU
	void Send( const std::string &message) 
	{
		/// NIE JESTEM PEWIEN CZY +1
		const auto ret = send(sock, message.c_str(), message.size(), 0);
		if (ret < 0)
			throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
	}

	//OTRZYMYWANIE PAKIETU
	void Recv(char buf[], unsigned bufLeng) const
	{
		int bytesReceived = recv(sock, buf, bufLeng, 0);
	}
};

struct pakiet {
private:
	unsigned short operacja;
	unsigned short odpowiedz;
	unsigned short id;
	unsigned short ack;
public:
	pakiet(unsigned short opr, unsigned short res, short id, short ack) {
		this->operacja[0] = opr;
		this->odpowiedz = res;
		this->id = id;
		this->ack = ack;
	}

	pakiet(char rawData[], unsigned short size) {
		if (size > 2) throw std::exception("To large buffor!!!");

		unsigned short buff = rawData[0];
		operacja = 0 | ((buff >> 4) & 0x0F);
		odpowiedz = 0 | ((buff >> 1) & 0x07);
		id = 0 | ((buff & 0x01) << 3);

		buff = rawData[1];
		id |= ((buff >> 5) & 0x07);
		ack = 0 | ((buff >> 4) & 0x01);
	}

	std::string convertToSend() {
		std::string rt;
		char buff = 0;

		buff |= (operacja << 4);
		buff |= (odpowiedz << 1);
		buff |= (id >> 3);
		rt.push_back(buff);

		buff = 0;
		buff |= (id << 5);
		//	buff |= (ack << 4);//usunac 
		//	buff |= (0x0F);// usunac
		rt.push_back(buff);

		return rt;
	}

	bool comparePacets(pakiet pakietOtrzymany)
	{
		if (6 == pakietOtrzymany.getOperation() && odpowiedz == pakietOtrzymany.getResponse() && id == pakietOtrzymany.getId()) return true;
		return false;
	}

	unsigned short getOperation() const {
		return operacja;
	}

	unsigned short getResponse() const
	{
		return odpowiedz;
	}

	unsigned short getAckFlag() const
	{
		return ack;
	}

	unsigned short getId() const
	{
		return id;
	}
};
// id#1 | op#GEN | time#12:00 : 00.000 |//odpowiedŸ

const std::string ipAddress = "25.50.98.211";
const unsigned int port = 19975;

//generowanie id,		 ->GEN odpowiedŸ w polu IDENTYFIKATOR
//oczekiwanie			 ->WAI
//start rozgrywki		 ->STA
//przes³anie liczby L	 ->NUM, w polu ODPOWIEDZI
//przes³anie liczby prób ->ATT	w polu ODPOWIEDZI
//przesylanie wyniku	 ->TRY  w polu ODPOWIEDZI
//odpowiedz na wynik	 ->ANS  w polu ODPOWIEDZI
//zakonczenie polaczenia ->EXI  

int main()
{
	//Inicjalizacja WinSock
	WSASession Session;

	//Creat socket
	TCPSocket Socket;

	//Connection 
	Socket.connection(ipAddress,port);

	//Sending message
	std::string message = "Duupa!";
	Socket.Send(message);

	//Receiving message
	char buf[64]; unsigned int bufLeng = 64;
	Socket.Recv(buf, bufLeng);

	//Sprawdzenie
	std::cout << buf << std::endl;
	std::cin.ignore(2);
	
//	std::time_t result = std::time(nullptr);
//	std::cout << std::asctime(std::localtime(&result)) << result << " seconds since the Epoch\n";



	std::cin.ignore(2);

	return 0;
}