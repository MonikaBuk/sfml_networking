//
// Created by monik on 28/10/2023.
//

#ifndef SFMLGAME_CHATBOXUI_H
#define SFMLGAME_CHATBOXUI_H

#include "ButtonUI.h"
#include "InputFieldUI.h"

#include <vector>

// Forward declaration of ChatMessage
struct ChatMessage;

#include "UIElement.h"

class ChatBoxUI : public UIElement {
 public:
  ChatBoxUI();
  void innitElemets();

  // Other functions for managing chat messages

 private:
  InputFieldUI messageInput;
  ButtonUI sendButton;
  sf::RectangleShape chatBox;
  std::vector<ChatMessage> chatMessages;
  unsigned int visibleMessageCount;
  unsigned int firstVisibleMessage;
  // Other private members for scrolling and message management
};


#endif // SFMLGAME_CHATBOXUI_H
