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
  udpSocket = std::make_unique<sf::UdpSocket>();
  if (udpSocket->bind(serverPort) != sf::Socket::Done)
  {
    std::cerr << "Failed to bind and listen on port 54000" << std::endl;
  }
}

void Server::run()
{
  std::thread run_udp_server([&] {runUdpServer(); });
  run_udp_server.detach();
  runTcpServer();
}

void Server::runTcpServer()
{
  {
    while (running)
    {
      sf::TcpSocket& cSock =
        connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
      if (listener->accept(cSock) != sf::Socket::Done)
      {
        clientNum --;
        connections.pop_back();
        return;
      }
      else
      {
        std::cout << "accept done \n";
      }
      std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
      clientNum ++;
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
}
void Server::runUdpServer()
{
  while (running)
  {
    sf::Packet receivedPacket;
    sf::IpAddress sender;
    unsigned short port;
    std::cout << "Received UDP packet running from " << sender  << std::endl;
    auto status = udpSocket->receive(receivedPacket, sender, port);

    if (status == sf::Socket::Done)
    {
      std::cout << "Received UDP packet from " << sender << ":" << port << std::endl;
      for (auto& client : udpClientSockets)
      {
        sf::IpAddress clientIpAddress = sf::IpAddress::getLocalAddress();
        unsigned short clientPort = client;
        sf::Packet copyOfReceivedPacket = receivedPacket;
        if (client != port)
        {
          if (
            udpSocket->send(
              copyOfReceivedPacket, clientIpAddress, clientPort) !=
            sf::Socket::Done)
          {
            std::cerr << "Failed to send UDP packet to client "
                      << clientIpAddress << ":" << clientPort << std::endl;
          }
        }
      }
    }
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  static short clientID   = 0;
  short currentClientID   = ++clientID;
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
    if (static_cast<MessageType>(messageType) == MessageType::CHAR_CHOICE)
    {
      sendInfoForChosenCharacter(receivedPacket,copyPacket, currentClientID);
    }
    else if (static_cast<MessageType>(messageType) == MessageType::STATE)
    {
      int state;
      copyPacket >> state;
      if (state == 2)
      {
        if (clientNum == clientsWithCharNum)
        {
          sendInfoForGameStart(receivedPacket);
        }
        else
        {
          ChatMessage msg;
          sf::Packet serverMsg;
          msg.sender = "Server";
          msg.text = "Everyone must select a character before the game";
          serverMsg << msg;
          sendToEveryone(serverMsg);
        }
      }
    }
    else if(static_cast<MessageType>(messageType) == MessageType::NEW_CONNECTION)
    {
      int newUDPPortNum;
      copyPacket >> newUDPPortNum;
      udpClientSockets.push_back(newUDPPortNum);
      sendInfoForNewConnections();
    }
    else
    {
      sendToOthers(receivedPacket);
    }
    std::cout << "Received from " << IP.toString() << std::endl;
  }
  cSocket.disconnect();
}

//send options
void Server::sendToEveryone(sf::Packet& packet) {
  for (auto& connection : connections)
  {
    std::lock_guard<std::mutex> lck(mutex);

    if (connection->send(packet) != sf::Socket::Done)
    {
      std::cerr << "Failed to send packet to a client" << std::endl;
    }
  }
}
void Server::sendToSender(sf::Packet& packet) {
  std::lock_guard<std::mutex> lck(mutex);
  for (auto& connection : connections)
  {
    if (connection->getRemotePort() == portNum)
    {
      if (connection->send(packet) != sf::Socket::Done)
      {
        std::cerr << "Failed to send packet to a client" << std::endl;
      }
    }
  }
}
void Server::sendToOthers(sf::Packet& packet) {
  std::lock_guard<std::mutex> lck(mutex);
  for (auto& connection : connections)
  {
    if (connection->getRemotePort() != portNum)
    {
      if (connection->send(packet) != sf::Socket::Done)
      {
        std::cerr << "Failed to send packet to a client" << std::endl;
      }
    }
  }
}


//handling different type of info requests and send them back relevant info
void Server::sendInfoForNewConnections()
{
  sf::Packet connectionPacket;
  ConnectionMessage newConnection;
  newConnection.gameRunning = isGameIsRunning();
  newConnection.characterAvailability = characterAvailableID;
  connectionPacket << newConnection;
  sendToSender(connectionPacket);
}

void Server::sendInfoForGameStart(sf::Packet receivedPacket)
{
  for (int i = 0; i < characterAvailableID.size(); i++) {
    if (!characterAvailableID[i]) {
      characterChoosenID.push_back(i);
    }
  }
  for (auto& id : characterChoosenID)
  {
    OtherCharacters newChars;
    newChars.id = id;
    sf::Packet charPacket;
    charPacket << newChars;
    sendToEveryone(charPacket);
  }
  sendToEveryone(receivedPacket);
}
void Server::sendInfoForChosenCharacter(sf::Packet receivedPacket, sf::Packet copyPacket, short currentClientID)
{
  int charID;
  copyPacket >> charID;
  ChatMessage message;
  if (characterAvailableID[charID])
  {
    message.text = "Character Is available";
    clientsWithCharNum ++;
    for (int i = 0; i < characterOwnedBy.size(); ++i)
    {
      if (characterOwnedBy[i] == currentClientID)
      {
        characterAvailableID[i] = true;
        characterOwnedBy[i]     = 0;
        clientsWithCharNum --;
      }
    }
    characterOwnedBy[charID]     = currentClientID;
    characterAvailableID[charID] = false;
    sendToSender(receivedPacket);
  }
  else
  {
    message.text = "Character Is Unavialable";
  }
  message.sender = charID;
  sf::Packet serverMsg;
  serverMsg << message;
  sendToSender(serverMsg);
  sf::Packet unavCharPacket;
  UnavailableCharacter unavailableCharacters;
  unavailableCharacters.characterAvailability = characterAvailableID;
  unavCharPacket << unavailableCharacters;
  sendToEveryone(unavCharPacket);
}


// setters and getters
bool Server::isGameIsRunning() const
{
  return gameIsRunning;
}
void Server::setGameIsRunning(bool gameIsRunning)
{
  Server::gameIsRunning = gameIsRunning;
}
