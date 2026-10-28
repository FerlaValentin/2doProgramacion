#include "Model.hpp"

#include <array>

#include "Card.hpp"
#include "UnoErrorCodes.hpp"

void Model::prepareDrawPile(){
    std::array<Color, 4> colors = {Color::Red, Color::Yellow, Color::Green, Color::Blue};
    for(Color color : colors){
        for(int i = 0; i < 2; ++i){
            for(int num = min_card_number_; num <= max_card_number_; ++num){
                if(i || num)    draw_pile_.AddCard(Card(num, color, CardType::Number));
            }
            draw_pile_.AddCard(Card(color, CardType::Skip));
            draw_pile_.AddCard(Card(color, CardType::Reverse));
            draw_pile_.AddCard(Card(color, CardType::Draw_Two));
        }
    }
    for(int i = 0; i < 4; ++i){
        draw_pile_.AddCard(Card(Color::Null, CardType::Wild));
        draw_pile_.AddCard(Card(Color::Null, CardType::Wild_Draw_Four));
    }
    draw_pile_.DebugDeck(draw_pile_);
}

std::optional<UnoError> Model::setPlayers(int numOfPlayers){
    if(numOfPlayers < min_players_) return UnoError::TooFewPlayers;
    if(numOfPlayers > max_players_) return UnoError::TooManyPlayers;
    players_.reserve(numOfPlayers);
    while(players_.size() < players_.capacity())
        players_.emplace_back(Model::playerCount());

    return std::nullopt;
}

void Model::setFirstPlayer(){
    player_turn_ = rand()%(int)players_.size();
    printf("[FIRST_PLAYER]: %d\n", player_turn_);
}

void Model::setHands(){
    hands_.reserve(Model::playerCount());
    while(hands_.size() < hands_.capacity())
        hands_.emplace_back();
}