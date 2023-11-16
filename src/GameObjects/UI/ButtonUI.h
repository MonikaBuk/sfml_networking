//
// Created by monik on 28/10/2023.
//

#ifndef SFMLGAME_BUTTONUI_H
#define SFMLGAME_BUTTONUI_H
#include "UIElement.h"

class ButtonUI: public UIElement
{
 public:
  ButtonUI(sf::Font& font, int fontSize, sf::Color textColor, const sf::String& buttonFilePath, const sf::String& buttonText, sf::Vector2f position, sf::Vector2f size);
  ~ButtonUI() = default;
  void draw();
  float getWidth();
  sf::Vector2<float> getPosition();
  bool isInsidePoint(sf::Vector2f point) const;
  void onSelected(sf::Event event);

 private:
  //sf::RenderWindow& window;
  sf::Font& font;
  int fontSize;
  sf::Color textColor;
  sf::Vector2f position;
  sf::Vector2f scale;
  sf::Texture buttonTexture;
  GameObject buttonBox;
  sf::Text text;
  std::string buttonText;
  std::string buttonFilePath;
  bool selected;

 public:
  bool isSelected() const;
};

#endif // SFMLGAME_BUTTONUI_H
