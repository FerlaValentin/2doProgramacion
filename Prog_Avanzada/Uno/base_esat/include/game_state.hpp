#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "player.hpp"
#include "uno_types.hpp"
#include <vector>

class GameState {
 public:
  int turn(Direction dir);
  bool verifyMove() const;
  void processMove();

 private:
  void applyEffect();
  void addCardsToPlayer(int amount);
  void switchDirection();
  void skipPlayer();
  void switchColor();

  Deck draw_pile_;
  Deck discard_pile_;
  int n_players_;
  std::vector<Player> players_;
  Color current_color_;
  Direction direction_;
};

#endif
