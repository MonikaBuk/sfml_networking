//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

class Server
{
 public:
  void init();
  void run();
  void listen(sf::TcpSocket& cSocket);
  void send(sf::Packet& packet);
  std::atomic<bool> created = false;


 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;
  bool connectionMessageSent = false;
  std::unique_ptr<sf::TcpListener>listener;
  std::unique_ptr<sf::TcpSocket> socket;
  std::mutex mutex;
  bool  running = true;
  int portNum;
  bool gameIsRunning = false;

 public:
  bool isGameIsRunning() const;
  void setGameIsRunning(bool gameIsRunning);
};

#endif // SFMLGAME_SERVER_H
