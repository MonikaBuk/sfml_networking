//
// Created by monik on 23/10/2023.
//

#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow& window, Client* client) : GameState(window), client(client)
{
}
void GameMenu::createUserNameInput()
{
 // userNameInput = std::make_unique<InputFieldUI>(window, font, 12, sf::Color::Green, sf::Color::White, sf::Vector2f(25, 45), sf::Vector2f(50, 10));
  //userNameInput->setIsEnabled(true);
}
bool GameMenu::init()
{
  chatBox = std::make_unique<ChatBoxUI>(*client);

  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")){std::cerr << "Failed to load font.";}
 // createUserNameInput();
  if (chatBox) {
    chatBox->innitElements(font, "Data/Images/dark brown panel.png");
  } else {
    std::cerr << "chatBox is NULL." << std::endl;
  }

  return true;
}
void GameMenu::update(float dt)
{
  chatBox->updateLatestChatMessage();

}
void GameMenu::render()
{
  //userNameInput->draw();
  chatBox->draw();


}
void GameMenu::mouseClicked(sf::Event event) {
  std::cout << "click";
  chatBox->onClickSend(event);
}
void GameMenu::keyPressed(sf::Event event) {
  chatBox->handleStatus(event);

}

void GameMenu::textEntered(sf::Event event)
{
  // userNameInput->handleEvent(event);
  // test.setString(userNameInput->getInputText());
  chatBox->handleEvent(event);
}

