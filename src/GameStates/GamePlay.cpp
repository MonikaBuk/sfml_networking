//
// Created by monik on 23/10/2023.
//

#include "GamePlay.h"

#include <iostream>

GamePlay::GamePlay(sf::RenderWindow& window) : GameState(window) {}

void GamePlay::SetTileWithID(
  const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size,
  const tmx::TileLayer::Tile& tile)
{
  auto& current =
    *TILE_MAP.back().emplace_back(std::make_unique<Tile>(tile.ID, *tileMap));
  if (current.GetID() == 0)
  {
    current.GetSpite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  else
  {
    current.GetSpite()->setTextureRect(sf::IntRect(
      (current.GetID() * tile_size.x) - tile_size.x,
      0,
      tile_size.x,
      tile_size.y));
  }
  current.GetSpite()->setPosition((TILE_MAP.back().size() % MAP_COLUMNS) * tile_size.x, (TILE_MAP.back().size() / MAP_COLUMNS) * tile_size.y);
}
bool GamePlay::init()
{
  tmx::Map map;
  if (!tileMap->loadFromFile("Data/tilemap.png"))
  {
    std::cout<<"FAILED TO LOAD SPRITESHEET" << std::endl;
  }
  if (!map.load("Data/test_map.tmx"))
  {
    std::cout<<"FAILED TO LOAD MAP DATA" << std::endl;
  }
  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;

  auto& tile_size = map.getTileSize();

  TILE_MAP.reserve(map.getLayers().size());

  for (const auto& layer:map.getLayers())
  {
    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    TILE_MAP.back().reserve(tiles.size());
    for (const auto& tile :tiles)
    {
      SetTileWithID(MAP_COLUMNS, tile_size, tile);
    }

  }
  return true;
}
void GamePlay::update(float dt) {
  // Implementation of the update function
}

void GamePlay::mouseClicked(sf::Event event) {
  // Implementation of the mouseClicked function
}

void GamePlay::keyPressed(sf::Event event) {
  // Implementation of the keyPressed function
}

void GamePlay::render()
{
  window.clear(sf::Color::Black);
  for (const auto& layer: TILE_MAP)
  {
    for (const auto& tile: layer)
    {
      if(tile->GetID() != 0)
      {
        window.draw(*tile->GetSpite());
      }
    }
  }
}

