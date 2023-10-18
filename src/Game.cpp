
#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  // networking
  if(isServer)
  {
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
    client =  std::make_unique<Client>();
    client -> connect();
  }

  //tilemap
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

void Game::update(float dt)
{

}

void Game::render()
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

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

}
void Game::SetTileWithID(
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
