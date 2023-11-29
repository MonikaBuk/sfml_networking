//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H
#include "Character.h"

class Player
{
 private:
  Character playerCharacter;
  sf::Vector2f velocity;


 public:
  void onCollision(sf::Vector2f direction);
  void movePlayer(const float& dt);
};

#endif // SFMLGAME_PLAYER_H
