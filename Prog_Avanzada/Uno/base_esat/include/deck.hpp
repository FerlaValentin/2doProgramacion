#pragma once
#ifndef DECK_HPP
#define DECK_HPP

#include "interfaces/IDeck.hpp"

#include <vector>

#include "Card.hpp"

class Deck : public IDeck{
    public:
        //int size() const override;
        //const ICard& operator[](int index) const override;

        //void shuffle() override;
        //void swap(IDeck& other) override;

        //void move(IDeck& other,int destination=-1) override;
        //void move(IDeck& other,int origin, int destination=-1) override;
    private:
        std::vector<Card> cards_;
};

#endif