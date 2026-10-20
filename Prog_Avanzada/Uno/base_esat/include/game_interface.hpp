#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include "card.hpp"

class IGameInterface {
 public:
  virtual void printTopCard() = 0;
  virtual void printBacksideCard() = 0;
  virtual void printPlayerCards() = 0;
  virtual void printUnoButton() = 0;
  virtual Card askPlayer() = 0;
};

#endif
