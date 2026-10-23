#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include "ICard.hpp"

class Card : public ICard{
    public:
        Color getColor() override;
        int getValue() override; // Undefined if isSpecial = true
        bool isSpecial() override;
        bool skipsPlayer() override;
        bool changeDirection() override;
        int addPenaltyCards() override;
        bool changeColor() override;
};

#endif