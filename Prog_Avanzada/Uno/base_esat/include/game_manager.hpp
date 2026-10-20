#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "game_state.hpp"

class GameManager {
 public:
  void run();

 private:
  GameState gs_;
};

#endif
