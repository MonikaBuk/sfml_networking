//
// Created by m2-bukovics on 25/10/2023.
//

#include "Player.h"



void Player::movePlayer(const float& dt)
{
  velocity.x = 0.0f;
  velocity.y = 0.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    velocity.x -= playerCharacter->getSpeed();
    playerCharacter->direction = Character::LEFT;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    velocity.x += playerCharacter->getSpeed();
    playerCharacter->direction = Character::RIGHT;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    velocity.y -= playerCharacter->getSpeed();
    playerCharacter->direction = Character::UP;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    velocity.y += playerCharacter->getSpeed();
    playerCharacter->direction = Character::DOWN;
  }

  playerCharacter->GetObjSprite()->move(velocity * dt);
}

void Player::onCollision(sf::Vector2f direction) {
  if (direction.x < 0.0f)
  {
    velocity.x = 0.0f;
  }
  else if (direction.x > 0.0f)
  {
    velocity.x = 0.0f;
  }

  if(direction.y < 0.0f)
  {
    velocity.y = 0.0f;

  }
  else if(direction.y > 0.0f)
  {
    velocity.y = 0.0f;
  }

  if (direction.y > 0.0f) {
    velocity.y = 0.0f;
  }
}
void Player::assignCharacter(std::unique_ptr<Character> character) {
  playerCharacter = std::move(character);}
const std::unique_ptr<Character>& Player::getPlayerCharacter() const
{
  return playerCharacter;
}
