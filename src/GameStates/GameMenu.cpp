//
// Created by monik on 23/10/2023.
//

#include "GameMenu.h"
//#include "GamePlay.h"

GameMenu::GameMenu(sf::RenderWindow& window, Network* network, StateHandler& handler) : GameState(window), network(network), stateHandler(handler)
{
}
void GameMenu::createUserNameInput()
{
 userNameInput = std::make_unique<InputFieldUI>(window, font, 25, CustomColors::TxtBlue, CustomColors::BcktBlue, sf::Vector2f(35, 45), sf::Vector2f(30, 8), 10);
 textInputTittle.setFont(font);
 textInputTittle.setPosition((userNameInput->getPos().x),userNameInput->getPos().y - 50);
 textInputTittle.setString("Please enter your name:");
}

bool GameMenu::init()
{
  std::string buttonFilePath = "Data/Images/ui/blue_button05.png";
  if(!font.loadFromFile("Data/Fonts/Font/kenvector_future.ttf")){std::cerr << "Failed to load font.";}
  createUserNameInput();
  joinButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , buttonFilePath,
    "Join Game", sf::Vector2f(55, 45), sf::Vector2f(25, 10));
  hostButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , buttonFilePath,
    "Host Game", sf::Vector2f(20, 45), sf::Vector2f(25, 10));
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

  if (userNameInput->getIsEnabled())
  {
    window.draw(textInputTittle);
  }
}
void GameMenu::mouseClicked(sf::Event event)
{
  // just a local IP as for public IP I would have to connect to a website which, and request the information, but it might not work on school computer or for other security reasons
  sf::IpAddress localAddress = network->localIP;
  if (joinButton->isSelected() && joinButton->getIsEnabled())
  {
    if (network->clientConnect(localAddress))
    {
      network->getClient()->setServerHost(false);
      stateHandler.setState(new GameLobby(window, network, stateHandler));
    }
    return;
  }
  if (hostButton->isSelected() && hostButton->getIsEnabled())
  {
    if (!network->serverCreate)
    {
      network->createServer();
      network->clientConnect(localAddress);

      network->getClient()->setServerHost(true);
      stateHandler.setState(new GameLobby(window, network, stateHandler));
    }

    if (network->serverCreate && network->clientConnect(localAddress))
    {
      network->getClient()->setServerHost(true);
      stateHandler.setState(new GameLobby(window, network, stateHandler));
    }
    return;
  }
}
void GameMenu::keyPressed(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (userNameInput->getIsEnabled())
      {
        std::string newName;
        newName = userNameInput->getInputText();
        if (!newName.empty())
        {
          network->getClient()->setUserName(newName);
          userNameInput->setIsEnabled(false);
          hostButton->setIsEnabled(true);
          joinButton->setIsEnabled(true);
        }
      }
    }
  }
}

void GameMenu::textEntered(sf::Event event)
{
  userNameInput->handleEvent(event);
}
void GameMenu::mouseWheelScrolled(sf::Event event) {

}
void GameMenu::mouseMoved(sf::Event event) {
  //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  hostButton->onSelected(event);
  joinButton->onSelected(event);

}
