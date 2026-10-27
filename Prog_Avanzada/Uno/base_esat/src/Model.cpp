#include "Model.hpp"

#include <array>

#include "Number.hpp"
#include "Skip.hpp"
#include "Reverse.hpp"
#include "DrawTwo.hpp"
#include "Wild.hpp"
#include "WildDrawFour.hpp"
#include "UnoErrorCodes.hpp"

void Model::prepareDrawPile(){
    std::array<Color, 4> colors = {Color::Red, Color::Yellow, Color::Green, Color::Blue};
    for(Color color : colors){
        for(int i = 0; i < 2; ++i){
            for(int num = minCardNumber; num <= maxCardNumber; ++num){
                if(i || num)    draw_pile_.AddCard(Number(num, color, CardType::Number));
            }
            draw_pile_.AddCard(Skip(color, CardType::Skip));
            draw_pile_.AddCard(Skip(color, CardType::Reverse));
            draw_pile_.AddCard(Skip(color, CardType::Draw_Two));
        }
    }
    for(int i = 0; i < 4; ++i){
        draw_pile_.AddCard(Wild(Color::Null, CardType::Wild));
        draw_pile_.AddCard(WildDrawFour(Color::Null, CardType::Wild_Draw_Four));
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