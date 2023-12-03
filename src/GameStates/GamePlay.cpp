//
// Created by monik on 23/10/2023.
//

#include "GamePlay.h"

#include <cmath>
#include <iostream>
#include <algorithm>

void GamePlay::Map_Loading(const std::string& tmxPath,const std::string& imgPath, std::unique_ptr<sf::Texture>& tileMap,   std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP)
{
  tmx::Map map;
  if (!tileMap->loadFromFile(imgPath))
  {
    std::cout<<"FAILED TO LOAD SPRITESHEET" << std::endl;
  }
  if (!map.load(tmxPath))
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
      SetTileWithID(tileMap, TILE_MAP, MAP_COLUMNS, MAP_ROWS, tile_size, tile, 3);
    }
  }
}
void GamePlay::SetTileWithID(std::unique_ptr<sf::Texture>& tileMap,   std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
  const unsigned int MAP_COLUMNS, const unsigned int MAP_ROWS, const tmx::Vector2u& tile_size,
  const tmx::TileLayer::Tile& tile,float scale)
{
  int tilemap_row = tileMap->getSize().x /24;

  auto& current =
    *TILE_MAP.back().emplace_back(std::make_unique<Tile>(tile.ID, *tileMap));
  if (current.GetID() == 0)
  {
    current.GetSpite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  else
  {
    int idWithOffset = current.GetID()-1;
    current.GetSpite()->setTextureRect(
      sf::IntRect(idWithOffset % tilemap_row * tile_size.x,
                  (std::floor(idWithOffset /tilemap_row) * tile_size.y),
                  tile_size.x, tile_size.y));
  }
  current.GetSpite()->setScale(scale, scale);
  current.GetSpite()->setPosition(
    (((TILE_MAP.back().size()) - 1) % MAP_COLUMNS) * (tile_size.x * scale),
    (((TILE_MAP.back().size()) - 1) / MAP_ROWS) * tile_size.y *scale);
}
void GamePlay::DrawMap(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP)
{
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
GamePlay::GamePlay(sf::RenderWindow& window, Network* network, StateHandler& handler) : GameState(window), network(network), stateHandler(handler)
{
}

bool GamePlay::init()
{
  Map_Loading("Data/Images/floor_map.tmx", "Data/Images/Dungeon_24x24.png", tileMapFloor, TILE_MAP_FlOOR);
  Map_Loading("Data/walls_gamemap.tmx", "Data/Images/Dungeon_24x24.png", tileMapWall, TILE_MAP_Wall);
  bird = std::make_unique<Character>();
  racoon = std::make_unique<Character>();
  fox = std::make_unique<Character>();
  cat = std::make_unique<Character>();
  bird->innitCharacter(0, "Data/Images/characters/BIRDSPRITESHEET.png", sf::Vector2f (300,300),Character::RIGHT);
  racoon->innitCharacter(1, "Data/Images/characters/RACCOONSPRITESHEET.png", sf::Vector2f (window.getSize().x - 200,200),Character::LEFT);
  fox->innitCharacter(2, "Data/Images/characters/FOXSPRITESHEET.png", sf::Vector2f (window.getSize().x - 200,400),Character::LEFT);
  cat->innitCharacter(3, "Data/Images/characters/CATSPRITESHEET.png", sf::Vector2f (300,400),Character::LEFT);
  characters.push_back(std::move(bird));
  characters.push_back(std::move(cat));
  characters.push_back(std::move(fox));
  characters.push_back(std::move(racoon));
  playerCharacter = std::make_unique<Player>();
  int playerID = network->getClient()->getCharacterId();
  playerCharacter->assignCharacter(std::move(characters[playerID]));
  std::vector<int> otherPlayersList;
  otherPlayersList = network->getClient()->getOtherPlayers();
  otherPlayersList.erase(std::remove(otherPlayersList.begin(), otherPlayersList.end(), playerID), otherPlayersList.end());




  std::cout << "The player char num is " << playerID << "\n";
  std::cout << "The player char id num is " << playerCharacter->getPlayerCharacter()->getId() << "\n";

  for (int num : otherPlayersList) {
    std::cout << "Processing other char num: " << num << "\n";
    network->getClient()->otherCharacters.push_back(std::move(characters[num]));
  }

  return true;
}

void GamePlay::update(float dt)
{
  playerCharacter->movePlayer(dt);
  playerCharacter->getPlayerCharacter()->handleAnim(dt);

  for (const auto& player : network->getClient()->otherCharacters)
  {
    std::cout << player->getId() <<"\n";
    player->handleAnim(dt);
  }
  for (const auto& layer : TILE_MAP_Wall)
  {
    for (const auto& tile : layer)
    {
      if (
        tile->GetID() != 0 &&
        tile->getCollider().checkCollision(
          playerCharacter->getPlayerCharacter()->getCollider(),
          playerCharacter->direction))
      {
        playerCharacter->onCollision(playerCharacter->direction);
      }
    }
  }
  sf::Vector2f charPos = playerCharacter->getPlayerCharacter()->GetObjSprite()->getPosition();
  int playerState = playerCharacter->getPlayerCharacter()->getDirection();
  int id = playerCharacter->getPlayerCharacter()->getId();
  CharacterUpdatePacket playerUpdate;
  playerUpdate.newPosition = charPos;
  playerUpdate.characterID = id;
  playerUpdate.state =playerState;
  network->getClient()->sendPlayerUpdate(playerUpdate);

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
  DrawMap(TILE_MAP_FlOOR);
  DrawMap(TILE_MAP_Wall);
  playerCharacter->getPlayerCharacter()->drawObject();
  for (const auto& players : network->getClient()->otherCharacters)
  {
    players->drawObject();
  }

}
void GamePlay::textEntered(sf::Event event) {}
void GamePlay::mouseWheelScrolled(sf::Event event) {}
void GamePlay::mouseMoved(sf::Event event) {}
