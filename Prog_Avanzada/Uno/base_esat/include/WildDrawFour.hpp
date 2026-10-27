#pragma once
#ifndef WILD_DRAW_FOUR_HPP
#define WILD_DRAW_FOUR_HPP

#include "Card.hpp"

#include "CardType.hpp"

class WildDrawFour : public Card{
    public:
        Color getColor() override;
        bool skipsPlayer() override;
        int addPenaltyCards() override;
        bool changeColor() override;

        WildDrawFour(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }
    private:
        const Color color_;
        const CardType type_;
};

#endif