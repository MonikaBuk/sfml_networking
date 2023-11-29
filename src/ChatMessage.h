//
// Created by m2-bukovics on 01/11/2023.
//

#ifndef SFMLGAME_CHATMESSAGE_H
#define SFMLGAME_CHATMESSAGE_H
#include <iostream>
#include <Sfml/Network.hpp>

enum  MessageType
{
  CHAT = 1,
  STATE = 2,
  CONNECTION = 3
};

struct ChatMessage
{
  std::string text;
  std::string sender;
};
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message);

struct StateMessage
{
  int state;
};
sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message);
sf::Packet& operator >>(sf::Packet& packet, StateMessage& message);

struct ConnectionMessage
{
  std::string userName;
  bool gameRunning;
};
sf::Packet& operator <<(sf::Packet& packet, const ConnectionMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ConnectionMessage& message);
#endif // SFMLGAME_CHATMESSAGE_H
