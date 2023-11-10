
#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  // networking
  if(isServer)
  {
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
    client =  std::make_unique<Client>();
    client -> connect();
  }
  stateHandler.setState(new GameMenu(window, client.get()));
  stateHandler.init();
  return true;
}

void Game::update(float dt)
{
  stateHandler.update(dt);
}

void Game::render()
{
  stateHandler.render();
}

void Game::mouseClicked(sf::Event event)
{
  sf::Vector2i click = sf::Mouse::getPosition(window);
  stateHandler.mouseClicked(event);
}

void Game::keyPressed(sf::Event event)
{
  stateHandler.keyPressed(event);
}
void Game::textEntered(sf::Event event) {
  stateHandler.textEntered(event);
}
void Game::mouseWheelScrolled(sf::Event event) {
  stateHandler.onWheelScrolled(event);
}
