//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include "../GameObjects/UI/Message.h"
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
  void recieveChatMessage(sf::Packet& messagePacket);
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;
  sf::Packet messagePacket;

 private:
  std::unique_ptr<sf::TcpSocket> socket;

};

#endif // SFMLGAME_CLIENT_H
