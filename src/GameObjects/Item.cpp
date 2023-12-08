//
// Created by monik on 06/12/2023.
//

#include "Item.h"
void Item::collect(IItemConfig* collector)
{
  switch (type)
  {
    case Type::SPEED:
    {
      collector->increaseSpeed(1);
      break;
    }

    case Type::RADIUS:
    {
      collector->increaseRadius(1);
      break;
    }
  }
}