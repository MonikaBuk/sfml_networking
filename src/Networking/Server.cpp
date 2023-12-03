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
    else
    {
      std::cout << "accept done \n";
    }
    std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
    workers.emplace_back(
      [&]
      {
        listen(cSock);
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
  static short clientID = 0;
  short currentClientID = ++clientID;
  bool continue_receiving = true;

  while (continue_receiving)
  {
    sf::Packet receivedPacket;
    auto status           = cSocket.receive(receivedPacket);
    sf::Packet copyPacket = receivedPacket;
    if (status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false; // disconnected
      std::cout << "Disconnected" << std::endl;
    }
    int messageType;
    copyPacket >> messageType;
    sf::IpAddress IP = cSocket.getRemoteAddress();
    portNum          = cSocket.getRemotePort();
    if (static_cast<MessageType>(messageType) == 4)
    {
      int charID;
      copyPacket >> charID;
      ChatMessage message;
      if (characterAvailableID[charID])
      {
        message.text                 = "Character Is available";
        characterAvailableID[charID] = false;
        characterChoosenID.push_back(charID);
      }
      else
      {
        message.text = "Character Is Unavialable";
      }
      message.sender = charID;
      sf::Packet serverMsg;
      serverMsg << message;
      for (auto& connection : connections)
      {
        if (connection->getRemotePort() == portNum)
        {
          send(serverMsg, *connection);
          send(receivedPacket, *connection);
        }
      }
    }
    else if (static_cast<MessageType>(messageType) == 2)
    {
      int state;
      copyPacket >> state;
      if (state == 2)
      {
        for (auto& id : characterChoosenID)
        {
          OtherCharacters newChars;
          newChars.id = id;
          sf::Packet charPacket;
          charPacket << newChars;
          for (auto& connection : connections)
          {
            send(charPacket, *connection);
          }
        }
        for (auto& connection : connections)
        {
          send(receivedPacket, * connection);
        }
      }
    }
    else if(static_cast<MessageType>(messageType) == 7)
    {
      sf::Packet connectionPacket;
      ConnectionMessage newConnection;
      newConnection.gameRunning = isGameIsRunning();
      newConnection.characterAvailability = characterAvailableID;
      connectionPacket << newConnection;
      for (auto& connection : connections)
      {
        if (connection->getRemotePort() == portNum)
        {
          send(connectionPacket, *connection);
        }
      }
    }
    else
    {
      for (auto& connection : connections)
      {
        if (connection->getRemotePort() != portNum)
        {
          send(receivedPacket, *connection);
        }
      }
    }
    std::cout << "Received from " << IP.toString() << std::endl;
  }
  cSocket.disconnect();
}
void Server::send(sf::Packet& packet, sf::TcpSocket& connection) {
  std::lock_guard<std::mutex> lck(mutex);
      if (connection.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send packet to a client" << std::endl;
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


