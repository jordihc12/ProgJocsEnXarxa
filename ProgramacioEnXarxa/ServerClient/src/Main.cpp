#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <chrono>

void AcceptConnextions(std::vector<sf::TcpSocket*>* _clients, bool* _end)
{
	sf::TcpListener listener;

	sf::Socket::Status status = listener.listen(50000);

	if (status != sf::Socket::Status::Done)
		return;

	while (!(*_end))
	{
		sf::TcpSocket* sock = new sf::TcpSocket();

		//Accept
		status = listener.accept(*sock);

		if (status != sf::Socket::Status::Done)
		{
			delete sock;
			continue;
		}
		_clients->push_back(sock);
		std::cout << "client connected" << std::endl;
		//Save clients
	}
}

void EnvioPeriodico(std::vector<sf::TcpSocket*>* _clients, bool* _end)
{
	sf::Packet pack;
	std::string str = "Mensaje desde servidor";

	pack << str;

	while (!(*_end))
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		for (size_t i = 0; i < _clients->size(); i++)
		{
			sf::Socket::Status status = _clients->at(i)->send(pack);
			switch (status)
			{
			case sf::Socket::Done:
				continue;
			case sf::Socket::Disconnected:
				_clients->at(i)->disconnect();
				delete _clients->at(i); 
				_clients->erase(_clients->begin() + i);
				i--;
				std::cout << "Client disconnected" << std::endl;
				continue;
			default:
				break;
			}
		}
	}
}

int main()
{
	std::vector<sf::TcpSocket*> clients;
	char opc;
	bool end = false;

	std::thread tAccepts(AcceptConnextions, &clients, &end);
	tAccepts.detach();

	std::thread tSends(EnvioPeriodico, &clients, &end);
	tSends.detach();

	do
	{
		std::cin >> opc;
	} while (opc != 'e');
	end = true;

	return 0;
}