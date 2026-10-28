#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include "interfaces/ICard.hpp"

#include "CardType.hpp"

class Card : public ICard {
    public:
        Card(int value, Color color, CardType type):
            value_{value},
            color_{color},
            type_{type}
        {
        }
        Card(Color color, CardType type):
            value_{-1},
            color_{color},
            type_{type}
        {
        }

        Color getColor() const override {return color_;};
        int getValue() const override {return value_;};
        bool isSpecial() const override {return false;};
        bool skipsPlayer() const override {return false;};
        bool changeDirection() const override {return false;};
        int addPenaltyCards() const override {return -1;};
        bool changeColor() const override {return false;};

        CardType getCardType() const {return type_;};
    protected:
        const int value_;
        const Color color_;
        const CardType type_;
};

#endif
