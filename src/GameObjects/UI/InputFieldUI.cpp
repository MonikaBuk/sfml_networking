//
// Created by monik on 25/10/2023.
//

#include "InputFieldUI.h"
InputFieldUI::InputFieldUI(sf::RenderWindow& window, sf::Font& font, int fontSize, sf::Color textColor, sf::Color fillColor, sf::Vector2f position, sf::Vector2f size)
  : window(window), font(font), fontSize(fontSize), textColor(textColor), fillColor(fillColor), position(position), size(size)
{
  text.setFont(font);
  text.setCharacterSize(fontSize);
  text.setFillColor(textColor);
  inputBox.setSize(getPercentage(size));
  inputBox.setFillColor(fillColor);
  inputBox.setPosition(getPercentage(position));

}

  void InputFieldUI::handleEvent(sf::Event event)
  {
    if (getIsEnabled())
    {
      if (event.type == sf::Event::TextEntered)
      {
        if (event.text.unicode < 128)
        {
          if (event.text.unicode == '\b' && !inputText.empty())
          {
            inputText.pop_back();
          }
          else if (event.text.unicode != '\b')
          {
            inputText += static_cast<char>(event.text.unicode);
          }
          text.setString(inputText);
          text.setPosition(position.x + 10, position.y + 10);
        }
      }
    }

  }


  void InputFieldUI::draw()
  {
    if (getIsEnabled())
    {
      window.draw(inputBox);
      window.draw(text);
    }
  }

