#include "ConsoleController.hpp"

#include <optional>

void ConsoleController::prepareMatch(){
    view_.askNumPlayer();
    while(!model_.playerCount()){
        view_.readIntegerInput();
    }
}

void ConsoleController::run(){
    view_.printUNO();
    prepareMatch();
}