#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include "ICard.hpp"

#include <optional>
#include <vector>
#include <functional>

#include "CardType.hpp"

class Card : public ICard{
    public:
        Color getColor() override;
        int getValue() override; // Undefined if isSpecial = true
        bool isSpecial() override;
        bool skipsPlayer() override;
        bool changeDirection() override;
        int addPenaltyCards() override;
        bool changeColor() override;

        Card(std::optional<int> value, Color color, CardType type):
            value_{value},
            color_{color},
            type_{type}
        {

        }
    private:
        const std::optional<int> value_;
        const Color color_;
        const CardType type_;
        const std::optional<std::vector<std::function<void*>>> effect;
};

#endif