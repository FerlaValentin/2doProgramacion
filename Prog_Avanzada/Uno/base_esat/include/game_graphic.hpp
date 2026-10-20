#ifndef GAME_GRAPHIC_HPP
#define GAME_GRAPHIC_HPP

#include "game_interface.hpp"

class GameGraphic : public IGameInterface {
 public:
  Card askPlayer() override;

 private:
  void printTopCard() override;
  void printBacksideCard() override;
  void printPlayerCards() override;
  void printUnoButton() override;
};

#endif
