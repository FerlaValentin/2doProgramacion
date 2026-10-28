#include "Deck.hpp"

void Deck::DebugDeck(const Deck& d) const{
    for(size_t i = 0; i < d.cards_.size(); ++i){
        Card card = d.cards_.at(i);
        const char *color_str, *type_string;
        switch(card.getColor()){
            case Color::Blue: color_str = "Blue"; break;
            case Color::Red: color_str = "Red"; break;
            case Color::Green: color_str = "Green"; break;
            case Color::Yellow: color_str = "Yellow"; break;
            case Color::Null: color_str = "Null"; break;
        }
        switch(card.getCardType()){
            case CardType::Draw_Two: type_string = "Draw Two"; break;
            case CardType::Number: type_string = "Number"; break;
            case CardType::Skip: type_string = "Skip"; break;
            case CardType::Reverse: type_string = "Reverse"; break;
            case CardType::Wild: type_string = "Wild"; break;
            case CardType::Wild_Draw_Four: type_string = "Wild Draw Four"; break;
        }
        printf("[INDEX] %d [VALUE]: %d [COLOR] %s [TYPE] %s\n", i + 1, card.getValue(), color_str, type_string);
    }
}