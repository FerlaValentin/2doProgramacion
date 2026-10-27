#pragma once
#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "Card.hpp"

#include "CardType.hpp"

class Number : public Card{
    public:
        Color getColor() override;
        int getValue() override; // Undefined if isSpecial = true

        Number(int value, Color color, CardType type):
            value_{value},
            color_{color},
            type_{type}
        {}

    private:
        const int value_;
        const Color color_;
        const CardType type_;
};

#endif