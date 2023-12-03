//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include <Sfml/Network.hpp>
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include "../ChatMessage.h"

class Client
{
 public:
  void connect(sf::IpAddress& ipToConnect);
  void run();
  void sendChatMessage(const ChatMessage& message);
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;
  bool isMessageReceived() const;
  void setMessageReceived(bool messageReceived);
  const ChatMessage& getLastMessage() const;
  void setLastMessage(const ChatMessage& lastMessage);
  const std::string& getUserName() const;
  void setUserName(const std::string& userName);
  void handleStateMessage(sf::Packet& packet);
  void handleChatMessage(sf::Packet& packet);
  void sendSateMessage(const StateMessage& message);
  int getNewState() const;
  bool isStateChanged() const;
  void setStateChanged(bool stateChanged);
  void sendConnectionMessage(const ConnectionMessage& message);
  bool isServerHost() const;
  void setServerHost(bool serverHost);
  bool isGameIsRunning() const;
  void sendCharChoiceMessage(const CharacterChoosing& message);
  const std::vector<int>& getOtherPlayers() const;

 private:
  std::unique_ptr<sf::TcpSocket> socket;
  bool messageReceived;
  ChatMessage lastMessage;
  std::string  userName = "testName";
  sf::IpAddress ipAddress;
  bool serverHost= false;
  bool gameIsRunning = false;
  int newState;
  bool stateChanged= false;
  void handleConnectionMessage(sf::Packet& packet);
  int characterID;
  std::vector<int> otherPlayers;
  std::vector<bool> characterAvailablity;

 public:
  const std::vector<bool>& getCharacterAvailablity() const;

  int getCharacterId() const;
  void setCharacterId(int characterId);
  void handleCharChooseMessage(sf::Packet& packet);
  void handleOtherCharChooseMessage(sf::Packet& packet);
  void sendConnectionRequest(const NewConnection& message);
};

#endif // SFMLGAME_CLIENT_H
