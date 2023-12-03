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
  void send(sf::Packet& packet, sf::TcpSocket& connection);
  std::atomic<bool> created = false;
  bool isGameIsRunning() const;
  void setGameIsRunning(bool gameIsRunning);

  void sendToEveryone(sf::Packet& packet);
  void sendToSender(sf::Packet& packet);
  void sendToOthers(sf::Packet& packet);

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;
  std::unique_ptr<sf::TcpListener>listener;
  std::unique_ptr<sf::TcpSocket> socket;
  std::mutex mutex;
  bool  running = true;
  int portNum;
  bool gameIsRunning = false;
  std::vector<short>clientIDs[4];
  std::vector<bool>characterAvailableID = {true,true,true,true};
  std::vector<int> characterChoosenID;
  std::vector<int> characterOwnedBy ={0,0,0,0};
 public:

};

#endif // SFMLGAME_SERVER_H
