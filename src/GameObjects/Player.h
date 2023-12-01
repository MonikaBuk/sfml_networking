//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H
#include "Character.h"

class Player : public GameObject
{
 private:
  std::unique_ptr<Character> playerCharacter;

 public:
  const std::unique_ptr<Character>& getPlayerCharacter() const;

 private:
  sf::Vector2f velocity;


 public:
  void onCollision(sf::Vector2f direction);
  void movePlayer(const float& dt);
  void assignCharacter(std::unique_ptr<Character> character);
  void Draw();

};

#endif // SFMLGAME_PLAYER_H
