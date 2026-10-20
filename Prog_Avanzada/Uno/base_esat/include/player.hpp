#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "deck.hpp"

class Player {
 public:
  void playCard();
  void drawCard();
  void passTurn();
  void sayUno();
  Color chooseColor();

 private:
  Deck hand_;
};

#endif
