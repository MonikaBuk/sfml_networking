//
// Created by monik on 28/10/2023.
//

#include "ChatBoxUI.h"


ChatBoxUI::ChatBoxUI(Client& client) : client(client){}

void ChatBoxUI::innitElements(sf::Font& font, const sf::String& buttonFilePath)
{
  sendButton = std::make_unique<ButtonUI>(
    font, 10, CustomColors::TxtBlue , buttonFilePath,
    "send", sf::Vector2f(30, 95), sf::Vector2f(0.035, 0.035));
  messageInput = std::make_unique<InputFieldUI>(window,font, 10, CustomColors::TxtBlue, CustomColors::BcktBlue, sf::Vector2f (0,95), sf::Vector2f (30,5), 50);
  float combinedWidth = messageInput->getWidth() + sendButton->getWidth();
  sf::Vector2f oneThird = getPercentage(sf::Vector2f(33,33));
  chatBox.setSize(sf::Vector2f (combinedWidth, oneThird.y));
  chatBox.setPosition(0, window.getSize().y - chatBox.getSize().y);
  chatBox.setFillColor(CustomColors::BckGreen);
  chatBox.setOutlineThickness(3);
  chatBox.setOutlineColor(CustomColors::BrdGreen);
  m_text.setFont(font);
  m_text.setCharacterSize(11);
  m_text.setFillColor(CustomColors::TxtBlue);
  setIsEnabled(true);
}
void ChatBoxUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(chatBox);
    messageInput->draw();
    sendButton->draw();
    float y = messageInput->getPos().y - 15;
    for (const auto& message : chatMessages)
    {  std::string senderString  = message.sender + ": ";
      std::string tempMessageText = senderString + message.text;
      std::string  messageText;
      if (tempMessageText.length() > 33)
      {
        int emptySpaceInSender = senderString.length() -1;
        std::string t1;
        std::string t2;


        int lastEmptySpace;
        lastEmptySpace = tempMessageText.find_last_of(" ", 40);

        if (lastEmptySpace != emptySpaceInSender)
        {
          t1          = tempMessageText.substr(0, lastEmptySpace);
          t2          = tempMessageText.substr(lastEmptySpace);
        }
        else{
          t1 = tempMessageText.substr(0, 33);
          t2          = tempMessageText.substr(33);
        }
        y -= 15;
        messageText = t1 + "\n" + t2;
      }
      else
      {
        messageText = tempMessageText;
      }
      m_text.setStyle(sf::Text::Regular);
      m_text.setString(messageText);
      m_text.setPosition(15, y);
      window.draw(m_text);
      y -= 15;
    }
  }
}
void ChatBoxUI::handleEvent(sf::Event event)
{
  if (getIsEnabled())
  {
    if (messageInput)
    {
      messageInput->handleEvent(event);
    }
  }
}

void ChatBoxUI::handleStatus(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (!getIsEnabled())
      {
        setIsEnabled(true);
      }
      else
      {
        sendChatMessage();
      }
    }
    else if (event.key.code == sf::Keyboard::Escape && getIsEnabled())
    {
      setIsEnabled(false);
    }
  }
}

ChatBoxUI::~ChatBoxUI() = default;

void ChatBoxUI::sendChatMessage() {
  std::string messageString = messageInput->getInputText();

  if (!messageString.empty())
  {
    ChatMessage chatMessage;
    chatMessage.text   = messageString;
    chatMessage.sender = client.getUserName();
    client.sendChatMessage(chatMessage);
    chatMessage.sender = "You";
    addMessage(chatMessage);
  }
  messageInput->clearInput();
}
void ChatBoxUI::addMessage(ChatMessage& sentMessage)
{
  chatMessages.insert(chatMessages.begin(),sentMessage);
  if (chatMessages.size() >10)
  {
    chatMessages.pop_back();
  }
}

void ChatBoxUI:: updateLatestChatMessage() {
  if (client.isMessageReceived())
  {
    ChatMessage receivedMessage = client.getLastMessage();
   addMessage(receivedMessage);
    if (!receivedMessage.text.empty())
    {
      client.setMessageReceived(false);
    }
  }
}


void ChatBoxUI::onClickSend(sf::Event event)
{
  if (event.type ==  sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      sf::Vector2i click = sf::Mouse::getPosition(window);
      if(sendButton->isInside(static_cast<sf::Vector2f>(click)))
      {
        std::cout << "shit";
        sendChatMessage();
      }
    }
  }
}


