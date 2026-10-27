#pragma once
#ifndef REVERSE_HPP
#define REVERSE_HPP

#include "Card.hpp"

#include "CardType.hpp"

class Reverse : public Card{
    public:
        Color getColor() override;
        bool changeDirection() override;

        Reverse(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }
    private:
        const Color color_;
        const CardType type_;
};

#endif