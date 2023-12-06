//
// Created by monik on 05/12/2023.
//

#ifndef SFMLGAME_BOMB_H
#define SFMLGAME_BOMB_H

#include "GameObject.h"
class Bomb : public GameObject
{
 public:
  void innitBomb(const std::string& characterText);
  void spawnBomb(sf::Vector2f spawn_position, float dt);

 private:
  sf::Texture bombTexture;
  bool isSpawned = false;
  float detonationTime = 0.2 * 25.0;
  float current_durration = 0;

 public:
  bool getIsSpawned() const;
  void setSpawned(bool spawned);
  void draw();
};

#endif // SFMLGAME_BOMB_H
