//
// Created by monik on 05/12/2023.
//

#include "Bomb.h"
void Bomb::spawnBomb(sf::Vector2f spawnPosition, float dt)
{
  if (0 >= current_durration && isSpawned) {
    GetObjSprite()->setPosition(spawnPosition);
    std::cout<< "this gets called";
  }
  current_durration += dt;

  if (current_durration < detonationTime) {
    animation.Update(0, dt, false);
    GetObjSprite()->setTextureRect(animation.rect);
    std::cout<< "animation gets called";
  }
  else {
    GetObjSprite()->setPosition(-10.f, -10.f);
    isSpawned = false;
    current_durration = 0.f;
  }
}
void Bomb::innitBomb(const std::string& characterText)
{
  if(!bombTexture.loadFromFile(characterText))
  {
    std::cerr << "Bomb png did not load";
  };
  GetObjSprite()->setTexture(bombTexture);
  GetObjSprite()->setScale(0.5, 0.5);
  animation.initAnim(&bombTexture, sf::Vector2u(24,1), 0.2);
}
bool Bomb::getIsSpawned() const
{
  return isSpawned;
}
void Bomb::setSpawned(bool spawned)
{
  Bomb::isSpawned = spawned;
}
void Bomb::draw()
{
  if(isSpawned)
  {
    window.draw(*GetObjSprite());
  }

}
