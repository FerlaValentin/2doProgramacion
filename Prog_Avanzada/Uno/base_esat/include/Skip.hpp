#pragma once
#ifndef SKIP_HPP
#define SKIP_HPP

#include "Card.hpp"

#include "CardType.hpp"

class Skip : public Card{
    public:
        Color getColor() override;
        bool skipsPlayer() override;

        Skip(Color color, CardType type):
            color_{color},
            type_{type}
        {

        }
    private:
        const Color color_;
        const CardType type_;
};

#endif