#include "ConsoleController.hpp"

#include <string>
#include <optional>

void ConsoleController::prepareMatch(){
    view_.askNumPlayer();
    std::optional<int> input = std::nullopt;
    while(input.has_value() == false){
        input = view_.readIntegerInput();
    }
    printf("The number is: %d\n", input.value());
}

void ConsoleController::run(){
    view_.printUNO();
    prepareMatch();
}