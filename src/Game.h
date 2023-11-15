
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

#include "Networking/Client.h"
#include "Networking/Server.h"
//#include "Tmx/Tile.h"
//#include "tmxlite/Map.hpp"
//#include "tmxlite/TileLayer.hpp"
#include "GameStates/StateHandler.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GameMenu.h"
#include "GameStates/GameLobby.h"
class Game
{
 public:
  Game(sf::RenderWindow& window, bool server);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void textEntered(sf::Event event);
  void mouseWheelScrolled(sf::Event event);
  void mouseMoved(sf::Event event);
 // const std::unique_ptr<Client>& getClient() const;

 private:
  sf::RenderWindow& window;
  bool isServer = true;
  std::unique_ptr<Client> client = nullptr;

 public:


 private:
  std::unique_ptr<Server> server = nullptr;
  StateHandler stateHandler;
};

#endif // PLATFORMER_GAME_H
