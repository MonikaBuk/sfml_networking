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
  buttonBox.GetSprite()->setTexture(buttonTexture);
  buttonBox.GetSprite()->setPosition(getPercentage(position));
  buttonBox.GetSprite()->setScale(scale);
  sf::FloatRect textBounds = text.getLocalBounds();
  sf::FloatRect buttonBounds = buttonBox.GetSprite()->getGlobalBounds();

  float offsetX = (buttonBounds.width - textBounds.width) / 2.0f;
  float offsetY = (buttonBounds.height - textBounds.height) / 2.0f;

  text.setPosition(buttonBox.GetSprite()->getPosition().x + offsetX, buttonBox.GetSprite()->getPosition().y + offsetY);
}

void ButtonUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(*buttonBox.GetSprite());
    window.draw(text);
  }
}

float ButtonUI::getWidth()
{
  sf::FloatRect buttonBoxBounds = buttonBox.GetSprite()->getGlobalBounds();
  float buttonBoxWidth = buttonBoxBounds.width;
  return buttonBoxWidth;
}

sf::Vector2<float> ButtonUI::getPosition()
{
  sf::Vector2f buttonBoxPosition = buttonBox.GetSprite()->getPosition();

  return buttonBoxPosition;
}

bool ButtonUI::isInsidePoint(sf::Vector2f point) const
{
  sf::FloatRect rect = buttonBox.GetSprite()->getGlobalBounds();
  return (
    (point.x+position.x >= rect.left && point.x <= rect.left + rect.width &&
     point.y +position.y >= rect.top && point.y <= rect.top + rect.height));
}
