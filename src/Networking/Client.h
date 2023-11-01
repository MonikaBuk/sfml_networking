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
  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void run();
  void sendChatMessage(const ChatMessage& message);
   void receiveChatMessage(ChatMessage& message);
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;
  bool isMessageReceived() const;
  void setMessageReceived(bool messageReceived);
  const ChatMessage& getLastMessage() const;
  void setLastMessage(const ChatMessage& lastMessage);

 private:
  std::unique_ptr<sf::TcpSocket> socket;
  bool messageReceived;
  ChatMessage lastMessage;


};

#endif // SFMLGAME_CLIENT_H
