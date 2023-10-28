//
// Created by m2-bukovics on 25/10/2023.
//

#include "UIElement.h"

sf::Vector2f UIElement::getPercentage(const sf::Vector2f& newPosition) const {
  sf::Vector2f percentage;

  float xPercentage = (windowSize.x / 100.0f) * newPosition.x;
  float yPercentage = (windowSize.y / 100.0f) * newPosition.y;

  percentage.x = xPercentage;
  percentage.y = yPercentage;

  return percentage;
}