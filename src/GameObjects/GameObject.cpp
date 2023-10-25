//
// Created by m2-bukovics on 25/10/2023.
//

#include "GameObject.h"

GameObject::GameObject()
{
  objectSprite = std::make_unique<sf::Sprite>();
}


GameObject::GameObject(const int& ID, const sf::Texture& texture) : GameObject()
{
  objectSprite->setTexture(texture);
}
std::unique_ptr<sf::Sprite>& GameObject::GetSprite()
{
  return objectSprite;
}