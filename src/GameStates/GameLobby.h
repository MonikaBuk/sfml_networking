//
// Created by monik on 24/10/2023.
//

#ifndef SFMLGAME_GAMELOBBY_H
#define SFMLGAME_GAMELOBBY_H

#include "GameState.h"
#include "../GameObjects/UI/ChatBoxUI.h"
#include "StateHandler.h"

class GameLobby: public GameState
{
 public:
  GameLobby(sf::RenderWindow& window,Network* network, StateHandler& handler);;
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;
  void mouseWheelScrolled(sf::Event event) override;
  void mouseMoved(sf::Event event) override;

 private:
  Network* network;
  std::unique_ptr<ChatBoxUI> chatBox;
  sf::Text test;
  sf::Font font;
  StateHandler&  stateHandler;
};

#endif // SFMLGAME_GAMELOBBY_H
