//#include <iostream>
//#include <SFML/Network.hpp>
//#include <vector>
//#include <thread>
//#include <chrono>
//#include <mutex>
//
//std::mutex mtx;
//
//void Reception(sf::TcpSocket* socket) {
//    sf::Socket::Status status;
//    do
//    {
//        sf::Packet pack;
//        status = socket->receive(pack);
//        std::string str;
//        switch (status)
//        {
//        case sf::Socket::Done:
//            pack >> str;
//            std::cout << str;
//            break;
//        case sf::Socket::NotReady:
//            continue;
//        case sf::Socket::Disconnected:
//            return;
//        default:
//            continue;
//        }
//    } while (true);
//}
//
//sf::Socket::Status SendPartial(sf::Packet& pack, sf::TcpSocket* sock)
//{
//    sf::Socket::Status status;
//
//    do
//    {
//        status = sock->send(pack);
//    } while (status == sf::Socket::Partial);
//
//    return status;
//}
//
//int main() {
//
//    // New chat or existing chat ?
//    bool existingChat = false;
//    bool endProgram = false;
//
//    char answer;
//    std::cout << "Quieres abrir un chat(1) o unirte a uno existente(2)? (Responde con 1 o 2)" << std::endl;
//    std::cin >> answer;
//    sf::TcpSocket sock;
//    sf::Socket::Status status;
//    if (answer == '1') {
//        // SERVER 
//
//        std::cout << "Tu Ip Adress es:" << sf::IpAddress::getLocalAddress() << std::endl;
//        std::cout << "A que puerto quieres conectarte? Ex: 50000" << std::endl;
//        int port;
//        std::cin >> port;
//        system("CLS");
//        std::cout << "Chat abierto. Tu ip es: " << sf::IpAddress::getLocalAddress() << "y el puerto: " << port << std::endl;
//
//        sf::TcpListener listener;
//        status = listener.listen(port);
//        if (status != sf::Socket::Status::Done)
//        {
//            return -1;
//        }
//        status = listener.accept(sock);
//        if (status != sf::Socket::Status::Done)
//        {
//            listener.close();
//            return -1;
//        }
//        listener.close();
//    }
//    else if (answer == '2')
//    {
//        // CLIENT 
//
//        std::string serverIP;
//        int serverPort;
//
//        std::cout << "A que IP quieres conectarte? Ex: 127.0.0.1" << std::endl;
//        std::cin >> serverIP;
//        std::cout << "A que PUERTO quieres conectarte? Ex: 50000" << std::endl;
//        std::cin >> serverPort;
//
//        status = sock.connect(serverIP, serverPort);
//        //Controlar el error
//        if (status != sf::Socket::Status::Done)
//        {
//            std::cout << "OJO! ERROR EN LA CONXION." << std::endl;
//        }
//        else
//        {
//            system("CLS");
//            std::cout << "Has entrado en el servidor con ip: " << serverIP << " y puerto: " << serverPort << std::endl;
//        }
//
//    }
//    else
//    {
//        std::cout << "UPS! No has escrito lo que se te pedia:(" << std::endl;
//    }
//
//    sock.setBlocking(false);
//
//    //Este punto es com�n para cliente y servidor
//    std::thread tReceive(Reception, &sock);
//    tReceive.detach();
//    std::string str;
//    sf::Packet pack;
//    do
//    {
//        std::getline(std::cin, str);
//        pack << str;
//        status = SendPartial(pack, &sock);
//        if (status == sf::Socket::Disconnected)
//            break;
//    } while (str != "e");
//    sock.disconnect();
//    return 0;
//} 