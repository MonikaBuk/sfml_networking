//
// Created by monik on 24/10/2023.
//

#ifndef SFMLGAME_GAMELOBBY_H
#define SFMLGAME_GAMELOBBY_H

#include "GameState.h"

class GameLobby: GameState
{
  GameLobby(sf::RenderWindow& window);
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
};

#endif // SFMLGAME_GAMELOBBY_H
