#pragma once
#ifndef WILD_HPP
#define WILD_HPP

#include "Card.hpp"

#include "CardType.hpp"

class Wild : public Card{
    public:
        Color getColor() override;
        bool changeColor() override;

        Wild(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }
    private:
        const Color color_;
        const CardType type_;
};

#endif