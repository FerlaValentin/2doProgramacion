#pragma once
#ifndef DECK_HPP
#define DECK_HPP

#include "interfaces/IDeck.hpp"

#include <vector>

#include "Card.hpp"

class Deck : public IDeck{
    public:
        int size() const override {return cards_.size();};
        //const ICard& operator[](int index) const override;

        void shuffle() override;
        //void swap(IDeck& other) override;

        //void move(IDeck& other,int destination=-1) override;
        //void move(IDeck& other,int origin, int destination=-1) override;

        void AddCard(const Card& card) {cards_.emplace_back(card);}
        void DebugDeck(const Deck& d) const;
        
    private:
        std::vector<Card> cards_;
};

#endif