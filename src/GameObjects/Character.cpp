//
// Created by m2-bukovics on 25/10/2023.
//

#include "Character.h"
int Character::getHealth() const
{
  return health;
}
void Character::setHealth(int health)
{
  Character::health = health;
}
float Character::getSpeed() const
{
  return speed;
}
