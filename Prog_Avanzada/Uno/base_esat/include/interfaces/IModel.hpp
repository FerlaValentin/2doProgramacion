#pragma once
#ifndef UNO_INTERFACES_IMODEL_HPP
#define UNO_INTERFACES_IMODEL_HPP

#include "Direction.hpp"
#include "IDeck.hpp"

class IModel {
    public:
    virtual int playerCount() const = 0;
    // virtual int currentPlayer() const = 0;
    // virtual const IDeck& getDrawDeck() const = 0;
    // virtual const IDeck& getDiscardDeck() const = 0;
    // virtual const IDeck& getPlayerHand(int id) const = 0;
    // virtual Direction getPlayDirection() const = 0;
    // virtual bool isGameEnded() const = 0;
    // virtual int winner() const = 0; // -1 == None

    // virtual void drawCard() = 0;
    // virtual bool playCard(int cardIndex,bool unoSaid) = 0;

    // virtual IModel* clone() const = 0;
    
    virtual ~IModel() = default;
};

#endif // UNO_INTERFACES_IMODEL_HPP
