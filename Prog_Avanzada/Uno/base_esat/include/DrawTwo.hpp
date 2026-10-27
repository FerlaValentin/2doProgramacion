#pragma once
#ifndef DRAW_TWO_HPP
#define DRAW_TWO_HPP

#include "Card.hpp"

#include "CardType.hpp"

class DrawTwo : public Card{
    public:
        Color getColor() override;
        bool skipsPlayer() override;
        int addPenaltyCards() override;

        DrawTwo(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }
    private:
        const Color color_;
        const CardType type_;
};

#endif