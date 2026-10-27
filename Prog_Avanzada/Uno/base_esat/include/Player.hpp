#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "interfaces/IPlayer.hpp"

class Player : public IPlayer {
    public:
        //BoolAction pass() const {BoolAction::Null;};
        //ICard* cardSelected() const {return nullptr;};
        //bool drawWanted() const {return false;};
        //Color colorSelected() const {return Color::Null;};
        //BoolAction unoSaid() const {BoolAction::Null;};
        //bool accuseUno() const {return false;};
        //BoolAction wantChallenge() const {BoolAction::Null;};
        Player(int id):
            id_{id}
        {

        }
    //private:
        int id_;
};

#endif // UNO_INTERFACES_IPLAYER_HPP