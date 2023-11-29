//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_CHARACTER_H
#define SFMLGAME_CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
 private:
  int health;
  float speed = 100;

 public:
  float getSpeed() const;

 public:
  int getHealth() const;
  void setHealth(int health);

 private:
  Animation characterAnim;

 public:
  void Spawn();
  enum CharacterStates
  {
    HEALTHY = 1,
    DAMAGED = 2,
    DEAD = 3,
  };

  enum Direction
  {
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
    OTHER = 5,
  };

};

#endif // SFMLGAME_CHARACTER_H
