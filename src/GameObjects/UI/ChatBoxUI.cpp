//
// Created by monik on 28/10/2023.
//

#include "ChatBoxUI.h"


ChatBoxUI::ChatBoxUI(Client& client) : client(client){}

void ChatBoxUI::innitElements(sf::Font& font, const sf::String& buttonFilePath)
{
  sendButton = std::make_unique<ButtonUI>(
    font, 10, sf::Color::Green, buttonFilePath,
    "send", sf::Vector2f(30, 0), sf::Vector2f(0.05, 0.05));
  messageInput = std::make_unique<InputFieldUI>(window,font, 10, sf::Color::Black, sf::Color::White, sf::Vector2f (0,0), sf::Vector2f (30,3));
  float combinedWidth = messageInput->getWidth() + sendButton->getWidth();
  chatBox.setSize(sf::Vector2f (combinedWidth, 80));
  chatBox.setPosition(0, 0);
  chatBox.setFillColor(sf::Color::Blue);
  m_text.setFont(font);      // Assuming you have a font object
  m_text.setCharacterSize(12); // Adjust the character size as needed
  m_text.setFillColor(sf::Color::White);
  setIsEnabled(true);
}
void ChatBoxUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(chatBox);
    messageInput->draw();
    sendButton->draw();
    float y = 40; // Adjust this value to set the initial vertical position
    for (const auto& message : chatMessages)
    {
      // Render each received message on the chat box

      // Set text color
      m_text.setString(message.sender + ": " + message.text);
      m_text.setPosition(40, y);
      window.draw(m_text);
      y += 20;
    }
  }
}
void ChatBoxUI::handleEvent(sf::Event event) {
  if (getIsEnabled())
  {
    // Handle events for the chat box
    // ...

    // Delegate input handling to the input field
    if (messageInput)
    {
      messageInput->handleEvent(event);
      if (event.type == sf::Event::TextEntered)
      {
        if (event.text.unicode == 13)
        {
          std::string message = messageInput->getInputText();

          if (!message.empty())
          {
            std::string sender = "SenderName";
            sendChatMessage(message);

            //receiveChatMessage(message);
            messageInput->clearInput();
          }
        }
      }
    }
  }
}

ChatBoxUI::~ChatBoxUI() = default;

void ChatBoxUI::sendChatMessage(const std::string& message) {
  ChatMessage chatMessage;
  chatMessage.text = message;
  chatMessage.sender = "sender";
  addMessage(chatMessage);
  client.sendChatMessage(chatMessage);
}
void ChatBoxUI::addMessage(ChatMessage& sentMessage)
{
  chatMessages.push_back(sentMessage);

}

void ChatBoxUI:: updateLatestChatMessage() {
  if (client.isMessageReceived())
  {
    ChatMessage receivedMessage = client.getLastMessage();
    chatMessages.push_back(receivedMessage);
    std::cout <<"it gets here";
    if (!receivedMessage.text.empty())
    {

      client.setMessageReceived(false);
    }
  }
}