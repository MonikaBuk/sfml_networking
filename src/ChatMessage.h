//
// Created by m2-bukovics on 01/11/2023.
//

#ifndef SFMLGAME_CHATMESSAGE_H
#define SFMLGAME_CHATMESSAGE_H
#include <iostream>
#include <Sfml/Network.hpp>

struct ChatMessage {
  std::string text= "asd";
  std::string sender = "idk";
};
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message)
{
  return packet << message.text << message.sender;
}

sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message)
{
  return packet >> message.text >> message.sender;
}
#endif // SFMLGAME_CHATMESSAGE_H
