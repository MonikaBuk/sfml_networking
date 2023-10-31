//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include <Sfml/Network.hpp>
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

struct ChatMessage {
  std::string text= "asd";
  //std::string sender = "idk";
};

class Client
{
 public:
  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void run();
  void sendChatMessage(const ChatMessage& message);
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;

 private:
  std::unique_ptr<sf::TcpSocket> socket;
};

#endif // SFMLGAME_CLIENT_H
