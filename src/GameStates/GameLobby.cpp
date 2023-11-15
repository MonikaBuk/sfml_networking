//
// Created by monik on 24/10/2023.
//

#include "GameLobby.h"

GameLobby::GameLobby(sf::RenderWindow& window, Client* client) : GameState(window), client(client)
{
}
bool GameLobby::init()
{
  chatBox = std::make_unique<ChatBoxUI>(*client);

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cerr << "Failed to load font.";
  }
  if (chatBox)
  {
    chatBox->innitElements(font, "Data/Images/dark brown panel.png");
  }
  else
  {
    std::cerr << "chatBox is NULL." << std::endl;
  }
}
void GameLobby::update(float dt) {  chatBox->updateLatestChatMessage();}
void GameLobby::render() { chatBox->draw();}
void GameLobby::mouseClicked(sf::Event event) {  chatBox->onClickSend(event);
}
void GameLobby::keyPressed(sf::Event event) {chatBox->handleStatus(event);}
void GameLobby::textEntered(sf::Event event)
{
  chatBox->handleEvent(event);
}
void GameLobby::mouseWheelScrolled(sf::Event event) {
  chatBox->OnScroll(event);
}
void GameLobby::mouseMoved(sf::Event event) {}
