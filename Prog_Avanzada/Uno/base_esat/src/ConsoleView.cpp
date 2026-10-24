#include "ConsoleView.hpp"

#include <cstdio>
#include <conio.h>
#include <string>
#include <optional>

void ConsoleView::printUNO() const {
    std::puts("(==================================)");
    std::puts(R"(
    U     U   N     N    OOOOO
    U     U   NN    N   O     O
    U     U   N N   N   O     O
    U     U   N  N  N   O     O
    U     U   N   N N   O     O
    U     U   N    NN   O     O
     UUUUU    N     N    OOOOO
    )");
    std::puts("(==================================)");
}

void ConsoleView::askNumPlayer() const{
    std::puts("How many players are going to play?(2-10)");
}

std::optional<std::string> ConsoleView::readTextInput(){

}

std::optional<int> ConsoleView::readIntegerInput(){

}