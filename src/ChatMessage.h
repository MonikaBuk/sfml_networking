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
  CONNECTION = 3,
  CHAR_CHOICE = 4,
  CHARACTER_UPDATE = 5,
  OTHER_CHAR = 6,
  NEW_CONNECTION = 7,
  UNAV_CHAR = 8
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
  bool gameRunning;
  unsigned short serverPort;
  std::vector<bool> characterAvailability = {true,true,true,true};
};
sf::Packet& operator <<(sf::Packet& packet, const ConnectionMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ConnectionMessage& message);


struct CharacterChoosing
{
 int id;
};
sf::Packet& operator <<(sf::Packet& packet, const CharacterChoosing& message);
sf::Packet& operator >>(sf::Packet& packet, CharacterChoosing& message);

struct CharacterUpdatePacket {
  int characterID;
  sf::Vector2f newPosition;
  int state;
};
sf::Packet& operator <<(sf::Packet& packet, const CharacterUpdatePacket& message);
sf::Packet& operator >>(sf::Packet& packet, CharacterUpdatePacket& message);

struct OtherCharacters
{
  int id;
};
sf::Packet& operator <<(sf::Packet& packet, const OtherCharacters& message);
sf::Packet& operator >>(sf::Packet& packet, OtherCharacters& message);

struct NewConnection
{
  int localPort;
};
sf::Packet& operator <<(sf::Packet& packet, const NewConnection& message);
sf::Packet& operator >>(sf::Packet& packet, NewConnection& message);

struct UnavailableCharacter
{
  std::vector<bool> characterAvailability = {true,true,true,true};
};
sf::Packet& operator <<(sf::Packet& packet, const UnavailableCharacter& message);
sf::Packet& operator >>(sf::Packet& packet, UnavailableCharacter& message);


#endif // SFMLGAME_CHATMESSAGE_H
