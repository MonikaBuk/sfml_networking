//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include "../ChatMessage.h"
#include "../GameObjects/Character.h"
#include <Sfml/Network.hpp>
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

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
  void handleChatMessage(sf::Packet& packet);


  const std::string& getUserName() const;
  void setUserName(const std::string& userName);
  int getNewState() const;
  void sendSateMessage(const StateMessage& message);
  void handleStateMessage(sf::Packet& packet);
  bool isStateChanged() const;
  void setStateChanged(bool stateChanged);
  bool isServerHost() const;
  void setServerHost(bool serverHost);
  bool isGameIsRunning() const;
  void sendCharChoiceMessage(const CharacterChoosing& message);
  const std::vector<int>& getOtherPlayers() const;
  const std::vector<bool>& getCharacterAvailablity() const;
  int getCharacterId() const;

  void handleCharChooseMessage(sf::Packet& packet);
  void handleOtherCharChooseMessage(sf::Packet& packet);
  void sendConnectionRequest(const NewConnection& message);
  void handleUnavCharChooseMessage(sf::Packet& packet);

  void sendWelcomeMessage();

  std::vector<std::unique_ptr<Character>> otherCharacters;

 private:
  std::unique_ptr<sf::TcpSocket> TcpSocket;
  std::unique_ptr<sf::UdpSocket> UdpSocket;
  sf::IpAddress clientIpAddress;
  unsigned short localPort;
  unsigned short udpServerPort;
  bool messageReceived;
  ChatMessage lastMessage;
  std::string  userName = "testName";
  sf::IpAddress ipAddress;
  bool serverHost= false;
  bool gameIsRunning = false;
  int newState;
  bool stateChanged= false;
  bool characterIsSelected = false;

 public:
  bool isCharacterIsSelected() const;

 private:
  int characterID;
  std::vector<int> otherPlayers;
  std::vector<bool> characterAvailablity;

  void handleConnectionMessage(sf::Packet& packet);
  void handleCharacterUpdateMessage(sf::Packet& packet);


 public:
  void handleTCPMessages(MessageType messageType, sf::Packet& packet);
  void handleUdpMessage(MessageType messageType, sf::Packet& receivedPacket);
  void sendPlayerUpdate2(const CharacterUpdatePacket& message);
  void runUdpClient();
  void setCharacterId(int characterId);
};

#endif // SFMLGAME_CLIENT_H
