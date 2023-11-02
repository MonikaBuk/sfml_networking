//
// Created by m2-bukovics on 25/10/2023.
//

#include "GameObject.h"

GameObject::GameObject()
{
  objectSprite = std::make_unique<sf::Sprite>();
}


const std::unique_ptr<sf::Sprite>& GameObject::GetSprite() const
{
  return objectSprite;
}

