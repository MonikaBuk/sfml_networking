//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H

#include "../GameWindow.h"
#include "GameObjectFunctions/Animation.h"
#include "GameObjectFunctions/Collider.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject
{
 public:
  GameObject();
  GameObject(const int& ID, const sf::Texture& texture);
  ~GameObject() = default;
  const std::unique_ptr<sf::Sprite>& GetSprite() const;
  Collider getCollider(){return Collider(*GetSprite());};
  sf::RenderWindow& window = GameWindow::getWindow();
  sf::Vector2u windowSize = window.getSize();
  Animation animation;
  void drawObject();
  sf::Vector2f direction{0,0};

 private:
  std::unique_ptr<sf::Sprite> objectSprite;


 public:
  bool isInside(sf::Vector2i pos) const;
};

#endif // SFMLGAME_GAMEOBJECT_H
