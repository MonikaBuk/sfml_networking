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
bool UIElement::isClicked() {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isEnabled) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Check if the mouse click is within the UI element's collider
    Collider collider = getCollider();  // Assuming you have a getCollider() method
    sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

    return collider.checkCollision(Collider(*GetSprite()), mousePosFloat, true, true);
  }
  return false;
}