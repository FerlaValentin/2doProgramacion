#ifndef GAME_TERMINAL_HPP
#define GAME_TERMINAL_HPP

#include "game_interface.hpp"

class GameTerminal : public IGameInterface {
 public:
  Card askPlayer() override;

 private:
  void printTopCard() override;
  void printBacksideCard() override;
  void printPlayerCards() override;
  void printUnoButton() override;
};

#endif
