//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
# include "GameObjectFunctions/Collider.h"
#include "GameObjectFunctions/Animation.h"

class GameObject
{
 public:
  GameObject();
  GameObject(const int& ID, const sf::Texture& texture);
  ~GameObject() = default;
  std::unique_ptr<sf::Sprite>& GetSprite();
  Collider getCollider(){return Collider(*GetSprite());};
  Animation animation;

 private:
  std::unique_ptr<sf::Sprite> objectSprite;
};

#endif // SFMLGAME_GAMEOBJECT_H
