//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
# include "GameObjectFunctions/Collider.h"
#include "GameObjectFunctions/Animation.h"
#include <iostream>

class GameObject
{
 public:
  GameObject();
  GameObject(const int& ID, const sf::Texture& texture);
  ~GameObject() = default;
  const std::unique_ptr<sf::Sprite>& GetSprite() const;
  Collider getCollider(){return Collider(*GetSprite());};
  Animation animation;

 private:
  std::unique_ptr<sf::Sprite> objectSprite;


 public:
  bool isInside(sf::Vector2i pos) const;
};

#endif // SFMLGAME_GAMEOBJECT_H
