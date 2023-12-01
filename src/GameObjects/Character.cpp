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
void Character::handleAnim(float dt)
{
  switch (direction)
  {
    case Character::UP:
      animation.Update(8,dt, false);
      GetSprite()->setTextureRect(animation.rect);
      break;

    case Character::DOWN:
      animation.Update(1,dt, false);
      GetSprite()->setTextureRect(animation.rect);
      break;

    case Character::RIGHT:
      animation.Update(4,dt, false);
      GetSprite()->setTextureRect(animation.rect);
      break;

    case Character::LEFT:
      animation.Update(6,dt, false);
      GetSprite()->setTextureRect(animation.rect);
      break;

    case Character::OTHER:
      // Handle animation for OTHER direction
      break;

    default:
      // Handle the default case (optional)
      break;
  }
}
void Character::innitCharacter(const std::string & characterText, sf::Vector2f spawn_position, Direction direction1)
{
  if (!characterTexture.loadFromFile(characterText))
  {
    // Handle error (e.g., log an error message or throw an exception)
    std::cerr << "Failed to load texture: " << characterText << std::endl;
    return;
  }
  GetSprite()->setTexture(characterTexture);
  animation.initAnim(&characterTexture, sf::Vector2u(4,9), 0.3);
  GetSprite()->setPosition(spawn_position);
  direction = direction1;
}

void Character::draw()
{
  window.draw(*GetSprite());
}
