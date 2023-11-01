//
// Created by monik on 25/10/2023.
//

#ifndef SFMLGAME_FONTMANAGER_H
#define SFMLGAME_FONTMANAGER_H
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class FontManager
{
 public:

  FontManager();
  FontManager(const std::string& fontFilePath);
  ~FontManager() = default;
  std::shared_ptr<sf::Font> GetFont();

  // Get the number of fonts in the vector

 private:
  std::shared_ptr<sf::Font> font;

};


#endif // SFMLGAME_FONTMANAGER_H
