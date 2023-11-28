//
// Created by monik on 01/11/2023.
//
#include "ChatMessage.h"
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message)
{
  std::cout << "Serializing MessageType: " << static_cast<int>(message.type) << std::endl;

  return packet << static_cast<int>(message.type) << message.text << message.sender;
}

sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message)
{
  int messageType;
  packet >> messageType >> message.text >> message.sender;
  message.type = static_cast<MessageType>(messageType);
  std::cout << "Deserialized MessageType: " << static_cast<int>(message.type) << std::endl;
  return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message)
{
  return packet << static_cast<int>(message.type) << message.state;
}

sf::Packet& operator >>(sf::Packet& packet, StateMessage& message)
{
  int messageType;
  packet >> messageType >> message.state;
  message.type = static_cast<MessageType>(messageType);
  return packet;
}