//
// Created by monik on 23/10/2023.
//

#include "StateHandler.h"

void StateHandler::setState(GameState* newState)
{
  // Release resources of the current state
  delete currentState;
  currentState = nullptr;

  // Set the new state
  currentState = newState;

  // Initialize the new state
  if (currentState) {
    currentState->init();
  }
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
  //currentState->init();
}
void StateHandler::textEntered(sf::Event event) {
  currentState->textEntered(event);
}
void StateHandler::onWheelScrolled(sf::Event event) {  currentState->mouseWheelScrolled(event);}

void StateHandler::mouseMoved(sf::Event event)
{
  currentState->mouseMoved(event);}
void StateHandler::gameClosed(sf::Event event)
{
  currentState->gameClosed(event);
}
