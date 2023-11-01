//
// Created by monik on 01/11/2023.
//
#include "ChatMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message)
{
  return packet << message.text << message.sender;
}

sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message)
{
  return packet >> message.text >> message.sender;
}