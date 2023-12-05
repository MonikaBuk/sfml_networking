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
  birdButton = std::make_unique<ButtonUI>(
    font,
    20,
    CustomColors::TxtBlue,
    "Data/Images/characters/Bird.png",
    "",
    sf::Vector2f(15, 20),
    sf::Vector2f(12, 12));
  characterButtons.push_back(std::move(birdButton));
  catButton = std::make_unique<ButtonUI>(
    font,
    20,
    CustomColors::TxtBlue,
    "Data/Images/characters/CAT.png",
    "",
    sf::Vector2f(30, 20),
    sf::Vector2f(12, 12));
  characterButtons.push_back(std::move(catButton));
  foxButton = std::make_unique<ButtonUI>(
    font,
    20,
    CustomColors::TxtBlue,
    "Data/Images/characters/FOX.png",
    "",
    sf::Vector2f(50, 20),
    sf::Vector2f(12, 12));
  characterButtons.push_back(std::move(foxButton));
  racoonButton = std::make_unique<ButtonUI>(
    font,
    20,
    CustomColors::TxtBlue,
    "Data/Images/characters/RACCOON.png",
    "",
    sf::Vector2f(70, 20),
    sf::Vector2f(12, 12));
  characterButtons.push_back(std::move(racoonButton));
  chatBox = std::make_unique<ChatBoxUI>(*network->getClient());
  std::string ipAddressString = network->localIP.toString();
  ipToConnectText             = std::make_unique<CustomText>(
    font, 20, CustomColors::BcktBlue, " IP TO CONNECT: " + ipAddressString);
  waitText =
    std::make_unique<CustomText>(font, 30, sf::Color::White, "test");
  characterText =
    std::make_unique<CustomText>(font, 30, sf::Color::White, "choose a character:");
  characterText->setPosition(window.getSize().x/ 2 - characterText->getGlobalBounds().width/2, window.getSize().y/ 7 );
  waitText->setPosition(
    window.getSize().x / 2 - waitText->getGlobalBounds().width / 2,
    window.getSize().y / 2);
  waitText->setIsEnabled(false);
  bckImage->GetObjSprite()->setColor(sf::Color(255,255,255, 150));

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
  availableCharacters = network->getClient()->getCharacterAvailablity();
  for (int i = 0; i < 4; i++)
  {
    characterButtons[i]->setAvailable(availableCharacters[i]);
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
void GameLobby::render()
{
  // bckImage->draw();
  chatBox->draw();
  ipToConnectText->draw();
  waitText->draw();
  startButton->draw();
  for (auto& button : characterButtons)
  {
    button->draw();
  }
  characterText->draw();
;}
void GameLobby::mouseClicked(sf::Event event)
{
  chatBox->onClickSend(event);
  if (startButton->isSelected() && startButton->getIsEnabled())
  {
    if (!network->getClient()->isGameIsRunning())
    {
      StateMessage newSate;
      newSate.state = 2;
      network->getServer()->setGameIsRunning(true);
      network->getClient()->sendSateMessage(newSate);
      return;
    }
  }
  for (int i = 0; i < characterButtons.size(); ++i)
  {
    if (characterButtons[i]->isSelected() && characterButtons[i]->isAvailable())
    {
      CharacterChoosing msg;
      msg.id = i;
      network->getClient()->sendCharChoiceMessage(msg);
    }
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
  availableCharacters = network->getClient()->getCharacterAvailablity();
  for (int i = 0; i < 4; i++)
  {
    characterButtons[i]->setAvailable(availableCharacters[i]);
  }

 startButton->onSelected(event);
 for (auto& button : characterButtons)
 {
   button->onSelected(event);
 }
 chatBox->getSendButton()->onSelected(event);
}
