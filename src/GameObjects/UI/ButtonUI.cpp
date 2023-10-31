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
  sf::FloatRect textBounds = text.getLocalBounds();
  sf::FloatRect buttonBounds = buttonBox.getGlobalBounds();

  float offsetX = (buttonBounds.width - textBounds.width) / 2.0f;
  float offsetY = (buttonBounds.height - textBounds.height) / 2.0f;

  text.setPosition(buttonBox.getPosition().x + offsetX, buttonBox.getPosition().y + offsetY);
}

void ButtonUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(buttonBox);
    window.draw(text);
  }
}

float ButtonUI::getWidth()
{
  sf::FloatRect buttonBoxBounds = buttonBox.getGlobalBounds();
  float buttonBoxWidth = buttonBoxBounds.width;
  return buttonBoxWidth;
}