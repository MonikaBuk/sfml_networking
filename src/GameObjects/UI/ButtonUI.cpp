//
// Created by monik on 28/10/2023.
//

#include "ButtonUI.h"

ButtonUI::ButtonUI(
  sf::Font& font, int fontSize, sf::Color textColor, const sf::String& buttonFilePath,
  const sf::String& buttonText, sf::Vector2f position, sf::Vector2f scale)
  : font(font), fontSize(fontSize), textColor(textColor), buttonFilePath(buttonFilePath), buttonText(buttonText), position(position), scale(scale)
{
  text.setFont(font);
  text.setCharacterSize(fontSize);
  text.setFillColor(textColor);
  text.setString(buttonText);
  buttonTexture.loadFromFile(buttonFilePath);
  buttonBox.setTexture(buttonTexture);
  buttonBox.setPosition(getPercentage(position));
  buttonBox.setScale(scale);
}

void ButtonUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(buttonBox);
    window.draw(text);
  }
}