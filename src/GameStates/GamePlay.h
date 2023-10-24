//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEPLAY_H
#define SFMLGAME_GAMEPLAY_H
#include "../Tmx/Tile.h"
#include "GameState.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"


class GamePlay : public GameState
{
 public:
  GamePlay(sf::RenderWindow& window);
  std::unique_ptr<sf::Texture> tileMap =  std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;
   bool init()override;
   void update(float dt);
   void render() override;
   void mouseClicked(sf::Event event);
   void keyPressed(sf::Event event);

  void SetTileWithID(
    const unsigned int columns, const tmx::Vector2u& vector2,
    const tmx::TileLayer::Tile& tile);

};

#endif // SFMLGAME_GAMEPLAY_H
