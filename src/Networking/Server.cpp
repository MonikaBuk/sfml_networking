//
// Created by m2-bukovics on 04/10/2023.
//

#include "Server.h"


void Server::init()
{
  if (listener == nullptr) listener = std::make_unique<sf::TcpListener>();
  if (listener->listen(53000) != sf::Socket::Done)
  {
    // error
  }
}

void Server::run()
{
  while (running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
    // getting new connection
    // if invalid return
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

  // add pointer for new_connection and get reference to it
}


void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;
  char data[1028];
  std::size_t received;
  while (continue_receiving)
  {
    sf::Packet receivedPacket;
    //auto status = cSocket.receive(data, 1028, received);
    auto status = cSocket.receive(receivedPacket);

    if(status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false; // disconnected
      std::cout << "Disconnected" << std::endl;
    }
    sf::IpAddress IP = cSocket.getRemoteAddress();
    portNum = cSocket.getRemotePort();
    cSocket.send(receivedPacket);

    if(received < 1028) { data[received] = '\0';}
    send(data);
    std::cout <<reinterpret_cast<char*>(data) << '\n' << IP.toString();
  }
  cSocket.disconnect();
}

void Server::send(std::string buffer)
{

  auto message =  reinterpret_cast<char*>(buffer.data());
  std::lock_guard<std::mutex>lck(mutex);
  for (auto & connection : connections)
  {
    if (connection->getRemotePort() != portNum)
    {
      connection->send(message, buffer.size());
    }
  }
}

