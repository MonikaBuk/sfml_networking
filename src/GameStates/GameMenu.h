//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEMENU_H
#define SFMLGAME_GAMEMENU_H
#include <memory>
#include "GameState.h"
#include "../GameObjects/UI/InputFieldUI.h"
#include "../GameObjects/UI/ChatBoxUI.h"


class GameMenu: public GameState
{
 public:
  GameMenu(sf::RenderWindow& window, Client* client);
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;
  void mouseWheelScrolled(sf::Event event) override;
  void mouseMoved(sf::Event event) override;

  void createUserNameInput();

 private:
  Client* client;
  std::unique_ptr<InputFieldUI> userNameInput;
  std::unique_ptr<ButtonUI> hostButton;
  std::unique_ptr<ButtonUI> joinButton;

  sf::Text textInputTittle;
  sf::Font font;


};


#endif // SFMLGAME_GAMEMENU_H
