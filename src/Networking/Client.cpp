//
// Created by m2-bukovics on 04/10/2023.
//

#include "Client.h"
#include "../GameStates/GamePlay.h"


void Client::connect(sf::IpAddress& ipToConnect)
{
  ipAddress = sf::IpAddress::getLocalAddress();
  if (socket == nullptr)
    socket = std::make_unique<sf::TcpSocket>();
  if (socket->connect(ipAddress, 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
    ChatMessage newConnection;
    newConnection.text = "Is Connected. Say Hi!";
    newConnection.sender = userName;
    sendChatMessage(newConnection);
    std::thread run_thread ([&]{run();});
    run_thread.detach();
  }
  else
  {
    std::cout << "failed to connect";
  }
}

void Client::run()
{
  running = true;
  while (running && connected)
  {
    while(connected)
    {
      sf::Packet receivedPacket;
      auto status = socket->receive(receivedPacket);

      if (status ==sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket ->disconnect();
        break;
      }
      else if (status == sf::Socket::Status::Done)
      {
        int messageType;
        receivedPacket >> messageType;

        switch (static_cast<MessageType>(messageType))
        {
          case MessageType::CHAT:
            std::cout << "Received CHAT message" << std::endl;
            handleChatMessage(receivedPacket);
            break;
          case MessageType::STATE:
            std::cout << "Received STATE message" << std::endl;
            handleStateMessage(receivedPacket);
            break;
          case MessageType::CONNECTION:
            std::cout << "Received CONNECTION message" << std::endl;
            handleConnectionMessage(receivedPacket);
            break;
          default:
            std::cerr << "Received an unknown message type: " << messageType << std::endl;
            // Handle unexpected message type
            break;

        }
      }
      else
      {
        // Handle other receive status if needed
        std::cerr << "Failed to receive packet. Status: " << status << std::endl;
      }
    }
  }
}

void Client::handleChatMessage(sf::Packet& packet)
{
  ChatMessage chatMessage;
  if (packet >> chatMessage)
  {
    setLastMessage(chatMessage);
    setMessageReceived(true);
    std::cout << "Received: " << chatMessage.text << " from " << chatMessage.sender << std::endl;
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}
void Client::handleStateMessage(sf::Packet& packet)
{
  StateMessage stateMessage;
  packet >> stateMessage;

  // Handle state change
   newState = stateMessage.state;
   stateChanged = true;

  switch (newState)
  {
    case 1: // StateType::Lobby

      break;
    case 2: // StateType::InGame

      break;
    case 3: // StateType::GameOver

      break;
    default:
      std::cerr << "Received an unknown state: " << newState << std::endl;
      // Handle unexpected state
      break;
  }

}

void Client::handleConnectionMessage(sf::Packet& packet)
{
  ConnectionMessage connectionMessage;
  if (packet >> connectionMessage)
  {
    gameIsRunning = connectionMessage.gameRunning;
    std::cerr << gameIsRunning << std::endl;
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}

void Client::sendChatMessage(const ChatMessage& message) {
  if (connected && socket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (socket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send chat message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send chat message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendSateMessage(const StateMessage& message) {
  if (connected && socket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (socket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send state message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send state message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendConnectionMessage(const ConnectionMessage& message) {
  if (connected && socket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (socket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send connection message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send connection message. Socket not connected or invalid." << std::endl;
  }
}

bool Client::isMessageReceived() const
{
  return messageReceived;
}
void Client::setMessageReceived(bool messageReceived)
{
  Client::messageReceived = messageReceived;
}
const ChatMessage& Client::getLastMessage() const
{
  return lastMessage;
}
void Client::setLastMessage(const ChatMessage& message)
{
 lastMessage = message;
}
const std::string& Client::getUserName() const
{
  return userName;
}
void Client::setUserName(const std::string& userName)
{
  Client::userName = userName;
}

const sf::IpAddress& Client::getIpAddress() const
{
  return sf::IpAddress::getPublicAddress();
}
int Client::getNewState() const
{
  return newState;
}
void Client::setStateChanged(bool stateChanged)
{
  Client::stateChanged = stateChanged;
}
bool Client::isStateChanged() const
{
  return stateChanged;
}
bool Client::isServerHost() const
{
  return serverHost;
}
void Client::setServerHost(bool serverHost)
{
  Client::serverHost = serverHost;
}
bool Client::isGameIsRunning() const
{
  return gameIsRunning;
}
