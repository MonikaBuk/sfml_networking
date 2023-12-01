//
// Created by m2-bukovics on 04/10/2023.
//

#include "Server.h"
#include "../ChatMessage.h"

void Server::init()
{
  if (listener == nullptr) listener = std::make_unique<sf::TcpListener>();
  if (listener->listen(53000) != sf::Socket::Done)
  {
    std::cerr << "Failed to bind and listen on port 53000" << std::endl;
  }
}

void Server::run()
{

  while (running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
    if (listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back();
      return;
    }
    std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
    workers.emplace_back(
      [&]
      {
        listen(cSock);
        std::cout << "detected disconnect\n";
        std::lock_guard<std::mutex>lck(mutex);
        for (int i = 0; i < connections.size(); ++i)
        {
          if (connections[i]->getLocalPort() == cSock.getLocalPort()) continue;
          connections.erase(std::next(connections.begin(), i));
          break;
        }
      });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

}


void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;
  sf::Packet connectionPacket;
  ConnectionMessage newConnection;
  newConnection.gameRunning = isGameIsRunning();
  connectionPacket << newConnection;

  send(connectionPacket);

  while (continue_receiving)
  {
    sf::Packet receivedPacket;
    auto status = cSocket.receive(receivedPacket);

    ChatMessage msg;
    receivedPacket >> msg;

    if(status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false; // disconnected
      std::cout << "Disconnected" << std::endl;
    }
    sf::IpAddress IP = cSocket.getRemoteAddress();
    portNum = cSocket.getRemotePort();
    send(receivedPacket);
    std::cout << "Received from " << IP.toString() << std::endl;
  }
  cSocket.disconnect();
}

void Server::send(sf::Packet& packet) {
  std::lock_guard<std::mutex> lck(mutex);

  for (auto& connection : connections) {
    if (connection->getRemotePort() != portNum) {
      if (connection->send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send packet to a client" << std::endl;
      }
    }
  }
}
bool Server::isGameIsRunning() const
{
  return gameIsRunning;
}
void Server::setGameIsRunning(bool gameIsRunning)
{
  Server::gameIsRunning = gameIsRunning;
}


