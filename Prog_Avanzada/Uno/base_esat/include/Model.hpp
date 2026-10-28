#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include "interfaces/IModel.hpp"

#include <vector>
#include <optional>
#include <string>

#include "Deck.hpp"
#include "Player.hpp"

enum class UnoError;

class Model : public IModel{
    public:
        int playerCount() const override { return players_.size(); }
        // int currentPlayer() const override;
        // const IDeck& getDrawDeck() const override;
        // const IDeck& getDiscardDeck() const override;
        // const IDeck& getPlayerHand(int id) const override;
        // Direction getPlayDirection() const override;
        // bool isGameEnded() const override;
        // int winner() const override; // -1 == None

        // void drawCard() override;
        // bool playCard(int cardIndex,bool unoSaid) override;

        // IModel* clone() const override;

        void prepareDrawPile();
        std::optional<UnoError> setPlayers(int num_of_players);
        void setFirstPlayer();
        void setHands();

    private:
        static constexpr unsigned char min_players_ = 2, max_players_ = 10, min_card_number_ = 0, max_card_number_ = 9;
        unsigned char player_turn_;
        Deck draw_pile_, discard_pile_;
        std::vector<Deck> hands_;
        std::vector<Player> players_;
        
};

#endif