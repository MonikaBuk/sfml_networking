//
// Created by monik on 06/12/2023.
//

#ifndef SFMLGAME_ITEM_H
#define SFMLGAME_ITEM_H

#include "GameObject.h"
#include "IItemConfig.h"
class Item: public GameObject
{
  enum Type
  {
    SPEED,
    RADIUS,
  }type;

  void collect(IItemConfig* collector);
};

#endif // SFMLGAME_ITEM_H
