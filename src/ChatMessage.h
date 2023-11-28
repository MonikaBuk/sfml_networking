//
// Created by m2-bukovics on 01/11/2023.
//

#ifndef SFMLGAME_CHATMESSAGE_H
#define SFMLGAME_CHATMESSAGE_H
#include <iostream>
#include <Sfml/Network.hpp>

enum class MessageType : int {
  CHAT = 1,
  STATE = 2,
};

struct ChatMessage {
  MessageType type;
  std::string text;
  std::string sender;
};
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message);

struct StateMessage {
  MessageType type;
  int state;
};
sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message);
sf::Packet& operator >>(sf::Packet& packet, StateMessage& message);
#endif // SFMLGAME_CHATMESSAGE_H
