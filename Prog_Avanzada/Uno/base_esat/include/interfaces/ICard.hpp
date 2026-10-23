#pragma once
#ifndef UNO_INTERFACES_ICARD_HPP
#define UNO_INTERFACES_ICARD_HPP

#include "Color.hpp"

class ICard {
    public:
    virtual Color getColor() = 0;
    virtual int getValue() = 0; // Undefined if isSpecial = true
    virtual bool isSpecial() = 0;
    virtual bool skipsPlayer() = 0;
    virtual bool changeDirection() = 0;
    virtual int addPenaltyCards() = 0;
    virtual bool changeColor() = 0;
    virtual ~ICard() = default;
};

#endif // UNO_INTERFACES_ICARD_HPP
