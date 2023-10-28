//
// Created by monik on 23/10/2023.
//

#include "GameMenu.h"
GameMenu::GameMenu(sf::RenderWindow& window) : GameState(window) {}

void GameMenu::createUserNameInput()
{
  userNameInput = std::make_unique<InputFieldUI>(window, font, 12, sf::Color::Green, sf::Color::White, sf::Vector2f(25, 45), sf::Vector2f(50, 10));
  userNameInput->setIsEnabled(true);
std::cout << userNameInput->getIsEnabled();
}
bool GameMenu::init()
{
  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")){}
  createUserNameInput();
  return true;
}
void GameMenu::update(float dt)
{

}
void GameMenu::render()
{
  userNameInput->draw();


}
void GameMenu::mouseClicked(sf::Event event) {}
void GameMenu::keyPressed(sf::Event event) {}

void GameMenu::textEntered(sf::Event event)
{
  userNameInput->handleEvent(event);
  test.setString(userNameInput->getInputText());

}

