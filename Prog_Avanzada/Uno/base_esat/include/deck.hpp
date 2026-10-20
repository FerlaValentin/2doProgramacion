#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

class Card;

class Deck {
 public:
  void shuffle();
  int size() const;

 private:
  std::vector<Card> cards_;
};

#endif
