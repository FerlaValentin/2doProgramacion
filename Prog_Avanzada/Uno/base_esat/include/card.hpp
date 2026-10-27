#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include "interfaces/ICard.hpp"

class Card : public ICard {
    public:
        Color getColor() override {return Color::Null;};
        int getValue() override {return -1;};
        bool isSpecial() override {return false;};
        bool skipsPlayer() override {return false;};
        bool changeDirection() override {return false;};
        int addPenaltyCards() override {return -1;};
        bool changeColor() override {return false;};
};

#endif
