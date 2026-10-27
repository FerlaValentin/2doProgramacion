#include "Model.hpp"

#include "UnoErrorCodes.hpp"

int Model::playerCount() const{
    return players_.size();
}

void Model::prepareCards(){
    for(int num = 0; num <= 9; ++num){
        
    }
}

std::optional<UnoError> Model::setPlayers(int numOfPlayers){
    if(numOfPlayers < minPlayers) return UnoError::TooFewPlayers;
    if(numOfPlayers > maxPlayers) return UnoError::TooManyPlayers;
    players_.reserve(numOfPlayers);
    while(players_.size() < players_.capacity())
        players_.emplace_back(Model::playerCount());

    return std::nullopt;
}

void Model::setHands(){
    hands_.reserve(Model::playerCount());
    while(hands_.size() < hands_.capacity())
        hands_.emplace_back();
}