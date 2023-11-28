//
// Created by monik on 24/10/2023.
//

#ifndef SFMLGAME_GAMELOBBY_H
#define SFMLGAME_GAMELOBBY_H

#include "GameState.h"
#include "../GameObjects/UI/ChatBoxUI.h"
#include "StateHandler.h"
#include "../GameObjects/UI/CustomText.h"
#include "../GameObjects/UI/ButtonUI.h"

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
  std::unique_ptr<CustomText> ipToConnectText;
  sf::Font font;
  StateHandler&  stateHandler;
  std::unique_ptr<ButtonUI> startButton;
};

#endif // SFMLGAME_GAMELOBBY_H
