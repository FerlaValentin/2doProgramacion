#include "ConsoleController.hpp"

#include <optional>

void ConsoleController::prepareMatch(){
    view_.askNumPlayer();
    std::optional<std::string> input = std::nullopt;
    while(!input){
        view_.readTextInput(2);
    }
}

void ConsoleController::run(){
    view_.printUNO();
    prepareMatch();
}