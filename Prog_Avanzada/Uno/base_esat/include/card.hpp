#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include "interfaces/ICard.hpp"

#include "CardType.hpp"

class Card : public ICard {
    public:
        Card(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }

        Color getColor() const override {return Color::Null;};
        int getValue() const override {return -1;};
        bool isSpecial() const override {return false;};
        bool skipsPlayer() const override {return false;};
        bool changeDirection() const override {return false;};
        int addPenaltyCards() const override {return -1;};
        bool changeColor() const override {return false;};
    protected:
        Color color_;
        CardType type_;
};

#endif
