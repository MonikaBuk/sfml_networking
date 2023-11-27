//
// Created by monik on 16/11/2023.
//

#ifndef SFMLGAME_NETWORK_H
#define SFMLGAME_NETWORK_H

#include "Client.h"
#include "Server.h"

class Network
{
 public:
  Network();
  ~Network() = default;
  bool clientConnect();
  const std::unique_ptr<Client>& getClient() const;
  void  createServer();


 private:
  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;
  void runServer();
};

#endif // SFMLGAME_NETWORK_H
