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
        int playerCount() const override;
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

        void prepareCards();
        std::optional<UnoError> setPlayers(int num_of_players);
        void setHands();

    private:
        static constexpr unsigned char minPlayers = 2, maxPlayers = 10;
        Deck draw_pile_, discard_pile_;
        std::vector<Deck> hands_;
        std::vector<Player> players_;
};

#endif