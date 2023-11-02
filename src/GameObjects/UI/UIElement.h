//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_UIELEMENT_H
#define SFMLGAME_UIELEMENT_H

#include <SFML/Graphics.hpp>
#include "../GameObject.h"
#include "../../GameWindow.h"
#include "CustomColours.h"
class UIElement: public GameObject
{
 public:

  sf::RenderWindow& window = GameWindow::getWindow();
  sf::Vector2u windowSize = window.getSize();
  sf::Vector2f getPercentage(const sf::Vector2f& newPosition) const;

  bool getIsEnabled() const { return isEnabled; }
  void setIsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }

  bool isSelected() const { return selected; }
  void setSelected(bool selected) { this->selected = selected; }
  bool isClicked();




 private:
  // Member variables to store the state of the UI element
  bool isEnabled = true;
  bool selected;


};

#endif // SFMLGAME_UIELEMENT_H
