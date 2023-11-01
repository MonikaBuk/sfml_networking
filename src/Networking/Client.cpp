//
// Created by m2-bukovics on 04/10/2023.
//

#include "Client.h"

void Client::connect()
{
  sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
  if (socket == nullptr)
    socket = std::make_unique<sf::TcpSocket>();
  if (socket->connect(ipAddress, 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
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
 // std::thread input_thread([&]{input(*socket);});
  //input_thread.detach();
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
      else
      {
        ChatMessage chatMessage;
        if (receivedPacket >> chatMessage)
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
    }
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

void Client::receiveChatMessage(ChatMessage& message) {
  if (connected && socket) {
    sf::Packet messagePacket;

    if (socket->receive(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to receive chat message" << std::endl;
    } else {
      // Extract the chat message from the received packet
      messagePacket >> message; // Uses the operator>> overload
    }
  } else {
    std::cerr << "Failed to receive chat message. Socket not connected or invalid." << std::endl;
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
