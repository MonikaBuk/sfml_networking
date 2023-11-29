//
// Created by monik on 01/11/2023.
//
#include "ChatMessage.h"
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message)
{
  return packet << CHAT << message.text << message.sender;
}

sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message)
{
  packet >> message.text >> message.sender;
  return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message)
{
  return packet << STATE << message.state;
}

sf::Packet& operator >>(sf::Packet& packet, StateMessage& message)
{
  packet  >> message.state;
  return packet;
}