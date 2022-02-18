#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

void RecieveMessage(sf::TcpSocket* sock, bool* end)
{
	sf::Socket::Status status;
	do
	{
		sf::Packet pack;
		status = sock->receive(pack);

		std::string str;

		switch (status)
		{
		case sf::Socket::Done:
			pack >> str;
			std::cout << str << std::endl;
			break;
		case sf::Socket::Disconnected:
			*end = true;
			break;
		default:
			break;
		}
	} while (!(*end));
}

int main()
{
	sf::TcpSocket sock;
	sf::Socket::Status status = sock.connect("localhost", 50000);

	bool end = false;

	std::thread tSend(RecieveMessage, &sock, &end);
	tSend.detach();

	std::string str;

	do
	{
		std::cin >> str;
		sf::Packet pack;
		pack << str;
		sock.send(pack);

	} while (str != "e");

	end = true;

	sock.disconnect();

	return 0;
}