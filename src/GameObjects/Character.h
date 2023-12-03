//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_CHARACTER_H
#define SFMLGAME_CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
 public:
  int getHealth() const;
  void setHealth(int health);
  void handleAnim(float dt);
  void changePosition(float dt, sf::Vector2f charPos);
  enum  Direction
  {
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
    OTHER = 5,
  }direction;
  void innitCharacter(int id, const std::string& characterText, sf::Vector2f spawn_position, Direction direction1);
  float getSpeed() const;


  enum  CharacterStates
  {
    HEALTHY = 1,
    DAMAGED = 2,
    DEAD = 3,
  };
  void draw();


 private:
  Animation characterAnim;
  sf::Texture characterTexture;
  int health;
  float speed = 100.0;
  int ID;

 public:
  int getId() const;

 public:
  Direction getDirection() const;
};



#endif // SFMLGAME_CHARACTER_H
