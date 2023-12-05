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
  void runTcpServer();
  void listen(sf::TcpSocket& cSocket);

  std::atomic<bool> created = false;
  bool isGameIsRunning() const;
  void setGameIsRunning(bool gameIsRunning);

  void sendToEveryone(sf::Packet& packet);
  void sendToSender(sf::Packet& packet);
  void sendToOthers(sf::Packet& packet);

  void sendInfoForNewConnections();
  void sendInfoForGameStart(sf::Packet receivedPacket);
  void sendInfoForChosenCharacter(sf::Packet receivedPacket, sf::Packet copyPacket, short currentClientID);

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;
  std::unique_ptr<sf::TcpListener>listener;
  std::unique_ptr<sf::TcpSocket> tcpSocket;
  std::unique_ptr<sf::UdpSocket> udpSocket;
  std::mutex mutex;
  bool  running = true;
  int portNum;

  std::vector<int> udpClientSockets;

  bool gameIsRunning = false;

  //info needed for character selection
  std::vector<short>clientIDs[4];
  std::vector<bool>characterAvailableID = {true,true,true,true};
  std::vector<int> characterChoosenID;
  std::vector<int> characterOwnedBy ={0,0,0,0};
  unsigned short serverPort = 54000;


  void runUdpServer();
};

#endif // SFMLGAME_SERVER_H
