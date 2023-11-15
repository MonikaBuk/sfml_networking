//
// Created by monik on 23/10/2023.
//

#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow& window, Client* client) : GameState(window), client(client)
{
}
void GameMenu::createUserNameInput()
{
 userNameInput = std::make_unique<InputFieldUI>(window, font, 25, CustomColors::TxtBlue, sf::Color::White, sf::Vector2f(25, 45), sf::Vector2f(50, 10), 10);
 textInputTittle.setFont(font);
 textInputTittle.setPosition((userNameInput->getPos().x),userNameInput->getPos().y - 50);
 textInputTittle.setString("Please enter your name:");

}
bool GameMenu::init()
{
  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")){std::cerr << "Failed to load font.";}
  createUserNameInput();
  joinButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , "Data/Images/dark brown panel.png",
    "Join Game", sf::Vector2f(55, 35), sf::Vector2f(0.3, 0.15));
  hostButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , "Data/Images/dark brown panel.png",
    "Host Game", sf::Vector2f(25, 35), sf::Vector2f(0.3, 0.15));
  hostButton->setIsEnabled(false);
  joinButton->setIsEnabled(false);

  return true;
}
void GameMenu::update(float dt)
{
}
void GameMenu::render()
{
  userNameInput->draw();
  hostButton->draw();
  joinButton->draw();
  window.draw(textInputTittle);
}
void GameMenu::mouseClicked(sf::Event event) {
}
void GameMenu::keyPressed(sf::Event event) {


}

void GameMenu::textEntered(sf::Event event)
{
  userNameInput->handleEvent(event);
}
void GameMenu::mouseWheelScrolled(sf::Event event) {

}
void GameMenu::mouseMoved(sf::Event event) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  hostButton->onSelected(event);
  joinButton->onSelected(event);

}
