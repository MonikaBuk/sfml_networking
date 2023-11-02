//
// Created by monik on 25/10/2023.
//

#include "FontManager.h"

FontManager::FontManager()
{
  font = std::make_unique<sf::Font>();
}

FontManager::FontManager(const std::string& fontFilePath) : FontManager()
{
  font = std::make_shared<sf::Font>();
  if (!font->loadFromFile(fontFilePath)) {
    std::cout << "font did not load";
  }
}
std::shared_ptr<sf::Font> FontManager::GetFont()
{
  return font;
}
