#include "ConsoleController.hpp"

#include <string>
#include <optional>

namespace{
    void preparePlayers(ConsoleView& v, Model& m){
        v.askNumPlayer();
        while(!m.playerCount()){
            std::optional<int> player_amount_input = std::nullopt;

            player_amount_input = v.readIntegerInput();
            if(player_amount_input.has_value()){
                auto players_amount_setting_err = m.setPlayers(player_amount_input.value());
                if(players_amount_setting_err.has_value()) v.printUnoError(players_amount_setting_err.value());
            }
        }
    }
}

void ConsoleController::prepareMatch(){
    model_.prepareCards();
    preparePlayers(view_, model_);
    model_.setHands();
}

void ConsoleController::run(){
    view_.printUNO();
    prepareMatch();
}