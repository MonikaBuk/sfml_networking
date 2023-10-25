//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEMENU_H
#define SFMLGAME_GAMEMENU_H

#include "GameState.h"

class GameMenu: GameState
{
  GameMenu(sf::RenderWindow& window);
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
};


#endif // SFMLGAME_GAMEMENU_H
