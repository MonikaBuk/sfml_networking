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
  setIsEnabled(true);
}
void ChatBoxUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(chatBox);
    messageInput->draw();
    sendButton->draw();
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
        { // Enter key pressed
          // Send the message from the input field
          std::string message = messageInput->getInputText();
          // Make sure the message is not empty before sending
          if (!message.empty())
          {
            //std::string sender = "SenderName";
            sendChatMessage(message);
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
  //chatMessage.sender = sender;

  client.sendChatMessage(chatMessage);
}

