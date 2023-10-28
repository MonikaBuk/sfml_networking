
#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
  stateHandler.setState(new GameMenu(window));
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
  std::cout<<"fuck this shit";
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}



void Game::keyPressed(sf::Event event)
{
  stateHandler.keyPressed(event);
}
void Game::textEntered(sf::Event event) {
  stateHandler.textEntered(event);
}
