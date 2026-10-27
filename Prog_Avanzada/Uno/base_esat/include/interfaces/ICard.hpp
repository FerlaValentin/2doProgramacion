#pragma once
#ifndef UNO_INTERFACES_ICARD_HPP
#define UNO_INTERFACES_ICARD_HPP

#include "Color.hpp"

class ICard {
    public:
    virtual Color getColor() const = 0;
    virtual int getValue() const = 0; // Undefined if isSpecial = true
    virtual bool isSpecial() const = 0;
    virtual bool skipsPlayer() const = 0;
    virtual bool changeDirection() const = 0;
    virtual int addPenaltyCards() const = 0;
    virtual bool changeColor() const = 0;
    virtual ~ICard() = default;
};

#endif // UNO_INTERFACES_ICARD_HPP
