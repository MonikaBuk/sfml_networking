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
      std::cout << connections.size() << "current clients connected\n";
      if (listener->accept(cSock) != sf::Socket::Done)
      {
        connections.pop_back();
        std::cout << "client pobed back \n";
        return;
      }
      else
      {
        std::cout << "Accept new client done \n";
      }
      std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
      workers.emplace_back(
        [&]
        {
          listen(cSock);
          std::cout << connections.size() << "someone from server disconnected  " << cSock.getLocalPort() << std::endl;;
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
    auto status = udpSocket->receive(receivedPacket, sender, port);
    if (status == sf::Socket::Done)
    {
      // Handle the received UDP packet
      for (auto& client : connectedClients)
      {
        sf::IpAddress clientIpAddress   = sf::IpAddress::getLocalAddress();
        unsigned short clientPort       = client.udpPortNumber;
        sf::Packet copyOfReceivedPacket = receivedPacket;
        if (client.udpPortNumber != port)
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
          std::cout << " info for all char char";
          sendToEveryone(serverMsg);
        }
      }
    }
    else if (static_cast<MessageType>(messageType) == MessageType::BOMB_SPAWN)
    {
      std::cout << " bomb chosen char";
      sendToEveryone(receivedPacket);
    }
    else if(static_cast<MessageType>(messageType) == MessageType::NEW_CONNECTION)
    {
      clientNum++;
      int newUDPPortNum;
      std:: string  userName;
      copyPacket >> newUDPPortNum >> userName;
      ClientData newClient;
      newClient.udpPortNumber = newUDPPortNum;
      newClient.userName =  userName;
      newClient.clientID = clientNum;
      newClient.characterID = -1;
      connectedClients.push_back(newClient);
      sendInfoForNewConnections();
    }
    else if(static_cast<MessageType>(messageType) == MessageType::DISCONNECTION)
    {
      std::cout << "someone disconnected\n";
      std::string userName;
      copyPacket >> userName;
      std::cout << userName << "username disconnected\n";

      auto it = std::remove_if(
        connectedClients.begin(),
        connectedClients.end(),
        [&](const ClientData& client) { return client.userName == userName; });
      connectedClients.erase(it, connectedClients.end());
      break ;
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
      std::cerr << "Failed to send packet to a everyone" << std::endl;
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
        std::cerr << "Failed to send packet to a other client" << std::endl;
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
  std::cout << " game start info";
  sendToEveryone(receivedPacket);
}
void Server::sendInfoForChosenCharacter(sf::Packet receivedPacket, sf::Packet copyPacket, short currentClientID)
{
  int charID;
  copyPacket >> charID;
  ChatMessage message;
  if (characterAvailableID[charID])
  {
    std::cout << " info chosen char";
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
  std::cout << " unav  char";
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
