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
  const sf::IpAddress& getIpAddress() const;
  void handleStateMessage(sf::Packet& packet);
  void handleChatMessage(sf::Packet& packet);
  void sendSateMessage(const StateMessage& message);
  int getNewState() const;
  bool isStateChanged() const;
  void setStateChanged(bool stateChanged);
  void sendConnectionMessage(const ConnectionMessage& message);


 private:
  std::unique_ptr<sf::TcpSocket> socket;
  bool messageReceived;
  ChatMessage lastMessage;
  std::string  userName = "testName";
  sf::IpAddress ipAddress;
  bool serverHost= false;
  bool gameIsRunning = false;

 public:
  bool isGameIsRunning() const;

 public:
  bool isServerHost() const;
  void setServerHost(bool serverHost);

 private:
  int newState;
  bool stateChanged= false;

  void handleConnectionMessage(sf::Packet& packet);
};

#endif // SFMLGAME_CLIENT_H
