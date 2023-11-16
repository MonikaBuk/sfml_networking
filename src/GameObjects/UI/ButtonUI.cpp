//
// Created by monik on 28/10/2023.
//

#include "ButtonUI.h"

ButtonUI::ButtonUI(
  sf::Font& font, int fontSize, sf::Color textColor, const sf::String& buttonFilePath,
  const sf::String& buttonText, sf::Vector2f position, sf::Vector2f scale)
  : font(font), fontSize(fontSize), textColor(textColor), buttonFilePath(buttonFilePath), buttonText(buttonText), position(position), scale(scale)
{
  // Load button texture
  buttonTexture.loadFromFile(buttonFilePath);

  // Set up button sprite
  buttonBox.GetSprite()->setTexture(buttonTexture);

  // Calculate desired size based on scale
  float targetWidth = scale.x;
  float targetHeight = scale.y;

  // Set the size of the sprite
  buttonBox.GetSprite()->setScale(getPercentage(sf::Vector2f (targetWidth / buttonBox.GetSprite()->getLocalBounds().width, targetHeight / buttonBox.GetSprite()->getLocalBounds().height)));

  // Set position (scaled)
  buttonBox.GetSprite()->setPosition(getPercentage(position));

  // Set up text
  text.setFont(font);
  text.setCharacterSize(fontSize);
  text.setFillColor(textColor);
  text.setString(buttonText);

  // Center the text within the button
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

void ButtonUI::onSelected(sf::Event event)
{
  if (event.type == sf::Event::MouseMoved)
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (!selected)
    {
      if (isInsidePoint(static_cast<sf::Vector2f>(mousePos)))
      {
        buttonBox.GetSprite()->setColor(sf::Color(0,255,0));
        selected = true;
      }
    }
    else if (selected)
    {
      if (!isInsidePoint(static_cast<sf::Vector2f>(mousePos)))
      {
        buttonBox.GetSprite()->setColor(sf::Color(255,255,255));
        selected = false;
      }
    }
  }
}
bool ButtonUI::isSelected() const
{
  return selected;
}
