//
// Created by monik on 24/10/2023.
//

#include "GameLobby.h"
#include "GamePlay.h"

GameLobby::GameLobby(sf::RenderWindow& window, Network* network, StateHandler& handler) : GameState(window), network(network), stateHandler(handler)
{
}
bool GameLobby::init()
{
  if (!font.loadFromFile("Data/Fonts/Font/kenvector_future.ttf"))
  {
    std::cerr << "Failed to load font.";
  }
  std::string buttonFilePath = "Data/Images/ui/blue_button05.png";
  bckImage    = std::make_unique<BackgroundImage>("Data/Images/background.jpg");
  startButton = std::make_unique<ButtonUI>(
    font,
    20,
    CustomColors::TxtBlue,
    buttonFilePath,
    "Start",
    sf::Vector2f(37.5, 45),
    sf::Vector2f(25, 10));
  chatBox = std::make_unique<ChatBoxUI>(*network->getClient());
  std::string ipAddressString = network->localIP.toString();
  ipToConnectText             = std::make_unique<CustomText>(
    font, 20, CustomColors::BcktBlue, " IP TO CONNECT: " + ipAddressString);
  waitText =
    std::make_unique<CustomText>(font, 30, sf::Color::White, "test");
  waitText->setPosition(
    window.getSize().x / 2 - waitText->getGlobalBounds().width / 2,
    window.getSize().y / 2);
  waitText->setIsEnabled(false);

  if (!network->getClient()->isServerHost())
  {
    waitText->setIsEnabled(true);
    startButton->setIsEnabled(false);
    if (network->getClient()->isGameIsRunning())
    {
      waitText->setString("game is running \n please wait for next round :)");
      waitText->setPosition(
        window.getSize().x / 2 - waitText->getGlobalBounds().width / 2,
        window.getSize().y / 2);
    }
    else
    {
      waitText->setString("please wait for the host \n to  start the round :)");
      waitText->setPosition(
        window.getSize().x / 2 - waitText->getGlobalBounds().width / 2,
        window.getSize().y / 2);
    }
  }

  if (chatBox)
  {
    chatBox->innitElements(font, "Data/Images/ui/blue_button05.png");
  }
  else
  {
    return false;
  }
  return true;
}
void GameLobby::update(float dt)
{
  chatBox->updateLatestChatMessage();
}
void GameLobby::render() {
  bckImage->draw();
  chatBox->draw();
  ipToConnectText->draw();
  waitText->draw();
  startButton->draw();
;}
void GameLobby::mouseClicked(sf::Event event)
{
  chatBox->onClickSend(event);
  if (startButton->isSelected() && startButton->getIsEnabled())
  {
if(!network->getClient()->isGameIsRunning())
    {
      StateMessage newSate;
      newSate.state = 2;
      network->getClient()->sendSateMessage(newSate);
      stateHandler.setState(new GamePlay(window, network, stateHandler));
        network->getServer()->setGameIsRunning(true);

      return;
    }
    else
      return;
  }
}
void GameLobby::keyPressed(sf::Event event)
{
  chatBox->handleStatus(event);
}
void GameLobby::textEntered(sf::Event event)
{
  chatBox->handleEvent(event);
}
void GameLobby::mouseWheelScrolled(sf::Event event) {
  chatBox->OnScroll(event);
}
void GameLobby::mouseMoved(sf::Event event)
{
 startButton->onSelected(event);
 chatBox->getSendButton()->onSelected(event);
}
