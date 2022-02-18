#include <iostream>
#include <SFML/Network.hpp>

int main()
{
	sf::TcpSocket sock;
	sf::Socket::Status status = sock.connect("localhost", 50000);
	if (status != sf::Socket::Status::Done)
	{
		//Not connected
	}

	bool end = false;

	do
	{
		sf::Packet pack;
		status = sock.receive(pack);

		std::string str;

		switch (status)
		{
		case sf::Socket::Done:
			pack >> str;
			std::cout << str << std::endl;
			break;
		case sf::Socket::Disconnected:
			end = true;
			break;
		default:
			break;
		}
	} while (!end);

	return 0;
}