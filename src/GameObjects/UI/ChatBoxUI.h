//
// Created by monik on 28/10/2023.
//

#ifndef SFMLGAME_CHATBOXUI_H
#define SFMLGAME_CHATBOXUI_H


#include <vector>
#include "../../Networking/Client.h"
#include "UIElement.h"
#include "ButtonUI.h"
#include "InputFieldUI.h"

class ChatBoxUI : public UIElement {
 public:
  explicit ChatBoxUI(Client& client);;
  ~ChatBoxUI();
  void innitElements(sf::Font& font, const sf::String& buttonFilePa);
  void handleEvent(sf::Event event);
  void draw();
  void sendChatMessage(const std::string& message);
  void addMessage(ChatMessage& message);
  void updateLatestChatMessage();

  // Other functions for managing chat messages

 private:
  Client& client;
  std::unique_ptr<InputFieldUI> messageInput;
  std::unique_ptr<ButtonUI> sendButton;
  sf::RectangleShape chatBox;
  std::vector<ChatMessage> chatMessages;
  unsigned int visibleMessageCount =0;
  unsigned int firstVisibleMessage= 0;
  sf::Font m_font;
  sf::Text m_text;


};


#endif // SFMLGAME_CHATBOXUI_H
