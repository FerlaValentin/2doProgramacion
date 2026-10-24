#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include "IModel.hpp"
#include <vector>
#include "Deck.hpp"
#include "Player.hpp"

class Model : public IModel{
    public:
        int playerCount() const override;
        int currentPlayer() const override;
        const IDeck& getDrawDeck() const override;
        const IDeck& getDiscardDeck() const override;
        const IDeck& getPlayerHand(int id) const override;
        Direction getPlayDirection() const override;
        bool isGameEnded() const override;
        int winner() const override; // -1 == None

        void drawCard() override;
        bool playCard(int cardIndex,bool unoSaid) override;

        IModel* clone() const override;
    private:
        std::vector<Deck> hands_;
        std::vector<Player> players_;
};

#endif