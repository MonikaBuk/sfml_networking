//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEPLAY_H
#define SFMLGAME_GAMEPLAY_H
#include "../GameObjects/Character.h"
#include "../GameObjects/Player.h"
#include "../Tmx/Tile.h"
#include "GameState.h"
#include "StateHandler.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

class GamePlay : public GameState
{
 public:
  GamePlay(sf::RenderWindow& window,Network* network, StateHandler& handler);
  std::unique_ptr<sf::Texture> tileMapFloor =  std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP_FlOOR;
  std::unique_ptr<sf::Texture> tileMapWall =  std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP_Wall;
  std::vector<std::unique_ptr<Character>> characters;


   bool init()override;
   void update(float dt);
   void render() override;
   void mouseClicked(sf::Event event) override;
   void keyPressed(sf::Event event) override;
   void textEntered(sf::Event event) override;
   void mouseWheelScrolled(sf::Event event) override;
   void mouseMoved(sf::Event event) override;
   void Map_Loading(const std::string& tmxPath,const std::string& imgPath, std::unique_ptr<sf::Texture>& tileMap,   std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP_Wall);
   void DrawMap(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP);
   void SetTileWithID(
     std::unique_ptr<sf::Texture>& tileMap, std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
    const unsigned int columns, const unsigned int rows, const tmx::Vector2u& vector2,
    const tmx::TileLayer::Tile& tile, float scale);
  StateHandler&  stateHandler;
  Network* network;
  void CreatePlayer(int id, std::vector<std::unique_ptr<Character>>);

 private:
  std::unique_ptr<Character> bird;
  std::unique_ptr<Character> cat;
  std::unique_ptr<Character> fox;
  std::unique_ptr<Character> racoon;
  std::unique_ptr<Player> playerCharacter;


};

#endif // SFMLGAME_GAMEPLAY_H
