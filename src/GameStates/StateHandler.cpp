//
// Created by monik on 23/10/2023.
//

#include "StateHandler.h"



void StateHandler::setState(GameState* newState)
{
  currentState = newState;
}
void StateHandler::update(float dt)
{
  if (currentState)
    currentState->update(dt);
}
void StateHandler::render()
{
  if (currentState)
    currentState->render();
}

void StateHandler::mouseClicked(sf::Event event)
{
  if (currentState)
    currentState->mouseClicked(event);
}
void StateHandler::keyPressed(sf::Event event)
{
  if (currentState)
    currentState->keyPressed(event);
}
void StateHandler::init()
{
  currentState->init();
}
void StateHandler::textEntered(sf::Event event) {
  currentState->textEntered(event);
}
