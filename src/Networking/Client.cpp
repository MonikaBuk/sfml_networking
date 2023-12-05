//
// Created by m2-bukovics on 04/10/2023.
//

#include "Client.h"
#include "../GameStates/GamePlay.h"


void Client::connect(sf::IpAddress& ipToConnect)
{
  if (TcpSocket == nullptr)
    TcpSocket = std::make_unique<sf::TcpSocket>();

  if (TcpSocket->connect(ipToConnect, 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
    sendWelcomeMessage();

    // Set up and bind UDP socket
    UdpSocket = std::make_unique<sf::UdpSocket>();
    if (UdpSocket->bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
      std::cerr << "Failed to bind UDP socket" << std::endl;
      return;
    }
    localPort = UdpSocket->getLocalPort();
    NewConnection infoRequest;
    infoRequest.localPort = localPort;
    sendConnectionRequest(infoRequest);

    // Start the TCP thread
    std::thread run_thread([this] { run(); });
    run_thread.detach();

    // Start the UDP thread
    std::thread run_Udpthread([this] { runUdpClient(); });
    run_Udpthread.detach();
  }
  else
  {
    std::cout << "Failed to connect" << std::endl;
  }
}

void Client::run()
{
  running = true;
  while (running && connected)
  {
    while (connected)
    {
      sf::Packet receivedPacket;
      auto status = TcpSocket->receive(receivedPacket);
      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        TcpSocket->disconnect();
        break;
      }
      else if (status == sf::Socket::Status::Done)
      {
        int messageType;
        receivedPacket >> messageType;
        handleTCPMessages(
          static_cast<MessageType>(messageType), receivedPacket);
      }
      else
      {
        std::cerr << "Failed to receive packet. Status: " << status
                  << std::endl;
      }
    }
  }
}
/*
void Client::recieveUdpPackets()
{
  std::cout << "udp packet handling received\n";
  sf::Packet receivedPacketUdp;
  sf::IpAddress senderAddress;
  unsigned short senderPort;
  statusUdp = UdpSocket->receive(receivedPacketUdp, senderAddress, senderPort);

  std::cout << "udp packet handling received\n";
  if (statusUdp == sf::Socket::Done)
  {
    int messageType;
    receivedPacketUdp >> messageType;
    std::cout << "udp packet received\n";
    handleUdpMessage(static_cast<MessageType>(messageType), receivedPacketUdp);
    std::cout << "udp packet handling done\n";
  }
  else
  {
    std::cerr << "Failed to receive UDP packet. Status: " << statusUdp << std::endl;
  }
}
*/
void Client::runUdpClient()
{
  running = true;
  while (running && connected)
  {
    sf::Packet receivedPacket;
    sf::IpAddress sender;
    unsigned short port;

    // Receive the UDP packet first
    auto status = UdpSocket->receive(receivedPacket, sender, port);

    if (status == sf::Socket::Done)
    {
      int messageType;
      receivedPacket >> messageType;
      std::cout << "Received UDP packet from " << sender
                << " with messageType: " << messageType << std::endl;
      handleUdpMessage(static_cast<MessageType>(messageType), receivedPacket);
    }
  }
}

void Client::handleTCPMessages(MessageType messageType, sf::Packet& receivedPacket)
{
  switch (static_cast<MessageType>(messageType))
  {
    case MessageType::CHAT:
      std::cout << "Received CHAT message" << std::endl;
      handleChatMessage(receivedPacket);
      break;
    case MessageType::STATE:
      std::cout << "Received STATE message" << std::endl;
      handleStateMessage(receivedPacket);
      break;
    case MessageType::CONNECTION:
      std::cout << "Received CONNECTION message" << std::endl;
      handleConnectionMessage(receivedPacket);
      break;
    case MessageType::CHAR_CHOICE:
      std::cout << "Received Character message" << std::endl;
      handleCharChooseMessage(receivedPacket);
      break;
    case MessageType::OTHER_CHAR:
      std::cout << "Received Other Player message" << std::endl;
      handleOtherCharChooseMessage(receivedPacket);
      break;
    case MessageType::UNAV_CHAR:
      std::cout << "Received Unav char Player message" << std::endl;
      handleUnavCharChooseMessage(receivedPacket);
      break;
    case MessageType::CHARACTER_UPDATE:
      std::cout << "Received Updaye Player message" << std::endl;
      handleCharacterUpdateMessage(receivedPacket);
      break;
    default:
      std::cerr << "Received an unknown message type: " << messageType << std::endl;
      break;
  }
}
void Client::handleUdpMessage(MessageType messageType, sf::Packet& receivedPacket)
{
  switch (static_cast<MessageType>(messageType))
  {
    case MessageType::CHAT:
      std::cout << "Received CHAT message" << std::endl;
      handleChatMessage(receivedPacket);
      break;
    case MessageType::STATE:
      std::cout << "Received STATE message" << std::endl;
      handleStateMessage(receivedPacket);
      break;
    case MessageType::CONNECTION:
      std::cout << "Received CONNECTION message" << std::endl;
      handleConnectionMessage(receivedPacket);
      break;
    case MessageType::CHAR_CHOICE:
      std::cout << "Received Character message" << std::endl;
      handleCharChooseMessage(receivedPacket);
      break;
    case MessageType::OTHER_CHAR:
      std::cout << "Received Other Player message" << std::endl;
      handleOtherCharChooseMessage(receivedPacket);
      break;
    case MessageType::UNAV_CHAR:
      std::cout << "Received Unav char Player message" << std::endl;
      handleUnavCharChooseMessage(receivedPacket);
      break;
    case MessageType::CHARACTER_UPDATE:
      std::cout << "Received Updaye Player message" << std::endl;
      handleCharacterUpdateMessage(receivedPacket);
      break;
    default:
      std::cerr << "Received an unknown message type: " << messageType << std::endl;
      break;
  }
}

void Client::handleChatMessage(sf::Packet& packet)
{
  ChatMessage chatMessage;
  if (packet >> chatMessage)
  {
    setLastMessage(chatMessage);
    setMessageReceived(true);
    std::cout << "Received: " << chatMessage.text << " from " << chatMessage.sender << std::endl;
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}
void Client::handleStateMessage(sf::Packet& packet)
{
  StateMessage stateMessage;
  packet >> stateMessage;

  // Handle state change
   newState = stateMessage.state;
   stateChanged = true;

  switch (newState)
  {
    case 1:
      // StateType::Lobby
      break;
    case 2:
      // StateType::InGame
      break;
    case 3:
      // StateType::GameOver
      break;
    default:
      std::cerr << "Received an unknown state: " << newState << std::endl;
      // Handle unexpected state
      break;
  }
}

// handle received packets
void Client::handleConnectionMessage(sf::Packet& packet)
{
  ConnectionMessage connectionMessage;
  if (packet >> connectionMessage)
  {
    gameIsRunning = connectionMessage.gameRunning;
    udpServerPort = connectionMessage.serverPort;
    std::cerr << gameIsRunning << std::endl;
    characterAvailablity = connectionMessage.characterAvailability;
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}
void Client::sendWelcomeMessage()
{
  ChatMessage newConnection;
  newConnection.text = "Is Connected. Say Hi!";
  newConnection.sender = userName;
  sendChatMessage(newConnection);
}
void Client::handleCharChooseMessage(sf::Packet& packet)
{
  CharacterChoosing charMessage;
  if (packet >> charMessage)
  {
    characterID = charMessage.id;
  }
  else
  {
    std::cerr << "Failed to extract character message from received packet." << std::endl;
  }
}
void Client::handleOtherCharChooseMessage(sf::Packet& packet)
{
  OtherCharacters charMessage;
  if (packet >> charMessage)
  {
    otherPlayers.push_back(charMessage.id);
  }
  else
  {
    std::cerr << "Failed to extract other character message from received packet." << std::endl;
  }
}
void Client::handleUnavCharChooseMessage(sf::Packet& packet)
{
  UnavailableCharacter charMessage;
  if (packet >> charMessage)
  {
    characterAvailablity = charMessage.characterAvailability;
  }
  else
  {
    std::cerr << "Failed to extract unavailable character message from received packet." << std::endl;
  }
}
void Client::handleCharacterUpdateMessage(sf::Packet& packet)
{
  CharacterUpdatePacket charMessage;
  if (packet >> charMessage)
  {
    for(int i = 0; i < otherCharacters.size(); i++)
    {
      if(charMessage.characterID == otherCharacters[i]->getId())
      {
        otherCharacters[i]->changePosition(sf::Vector2f (charMessage.newPosition.x, charMessage.newPosition.y));
        otherCharacters[i]->movementDirection =  static_cast<Character::MovementDirection>(charMessage.state);
      }
    }
  }
  else
  {
    std::cerr << "Failed to extract character update message from received packet." << std::endl;
  }
}
// send  packets
void Client::sendChatMessage(const ChatMessage& message) {
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send chat message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send chat message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendSateMessage(const StateMessage& message) {
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send state message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send state message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendConnectionRequest(const NewConnection& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send connection message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send connection message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendCharChoiceMessage(const CharacterChoosing& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send character choice message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send connection message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendPlayerUpdate(const CharacterUpdatePacket& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send connection message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send player update message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendPlayerUpdate2(const CharacterUpdatePacket& message) {
  if (connected && UdpSocket) {
    sf::Packet updatePacket;
    sf::IpAddress testIp = sf::IpAddress::getLocalAddress();
    updatePacket << message;
    if (UdpSocket->send(updatePacket, testIp, 54000) != sf::Socket::Done) {
      std::cerr << "Failed to send player update udp message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send player update message. Socket not connected or invalid." << std::endl;
  }
}

// setters and getters
bool Client::isMessageReceived() const
{
  return messageReceived;
}
void Client::setMessageReceived(bool messageReceived)
{
  Client::messageReceived = messageReceived;
}
const ChatMessage& Client::getLastMessage() const
{
  return lastMessage;
}
void Client::setLastMessage(const ChatMessage& message)
{
 lastMessage = message;
}
const std::string& Client::getUserName() const
{
  return userName;
}
void Client::setUserName(const std::string& userName)
{
  Client::userName = userName;
}

int Client::getNewState() const
{
  return newState;
}
void Client::setStateChanged(bool stateChanged)
{
  Client::stateChanged = stateChanged;
}
bool Client::isStateChanged() const
{
  return stateChanged;
}
bool Client::isServerHost() const
{
  return serverHost;
}
void Client::setServerHost(bool serverHost)
{
  Client::serverHost = serverHost;
}
bool Client::isGameIsRunning() const
{
  return gameIsRunning;
}
int Client::getCharacterId() const
{
  return characterID;
}
void Client::setCharacterId(int characterId)
{
  characterID = characterId;
}
const std::vector<int>& Client::getOtherPlayers() const
{
  return otherPlayers;
}
const std::vector<bool>& Client::getCharacterAvailablity() const
{
  return characterAvailablity;
}

