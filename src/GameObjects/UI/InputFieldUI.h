//
// Created by monik on 25/10/2023.
//

#ifndef SFMLGAME_INPUTFIELDUI_H
#define SFMLGAME_INPUTFIELDUI_H
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class InputFieldUI :public UIElement
{
 public:
  InputFieldUI(sf::RenderWindow& window, sf::Font& font, int fontSize, sf::Color textColor, sf::Color fillColor, sf::Vector2f position, sf::Vector2f size);
  ~InputFieldUI() = default;
  void handleEvent(sf::Event event);
  void draw();
  const std::string& getInputText() const { return inputText; }
  float getWidth();
  void clearInput();

 private:
  sf::RenderWindow& window;
  sf::Font& font;
  int fontSize;
  sf::Color textColor;
  sf::Color fillColor;
  sf::Vector2f position;
  sf::Vector2f size;
  sf::RectangleShape inputBox;
  sf::Text text;
  std::string inputText;


};

#endif // SFMLGAME_INPUTFIELDUI_H
