//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEMENU_H
#define SFMLGAME_GAMEMENU_H
#include <memory>
#include "../GameObjects/UI/InputFieldUI.h"
#include "GameState.h"

#include "../GameObjects/UI/FontManager.h"


class GameMenu: public GameState
{
 public:
  GameMenu(sf::RenderWindow& window);
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;

  void createUserNameInput();

 private:
  std::unique_ptr<InputFieldUI> userNameInput;
  sf::Text test;
  sf::Font font;
  std::shared_ptr<FontManager> fontManager;

};


#endif // SFMLGAME_GAMEMENU_H
