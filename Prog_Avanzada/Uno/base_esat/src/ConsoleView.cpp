#include "ConsoleView.hpp"

#include <cstdio>
#include <conio.h>
#include <stdexcept>
#include <cassert>

#include "UnoErrorCodes.hpp"

namespace{
    void DeleteCharacter(std::string& input){
        printf("\b \b");
        input.pop_back();
    }
    bool IsEnterKey(char c){return c == 10 || c == 13;}
    void AddCharacter(std::string& input, char c, std::optional<size_t> max_size){    
        if(IsEnterKey(c)){
            printf("\n");
            input.push_back(c);
        }
        else{
            if(!max_size.has_value() || max_size.has_value() && input.size() < max_size){
                printf("%c",c);
                input.push_back(c);
            }
        }
    }
}

void ConsoleView::printUNO() const {
    std::puts("==================================");
    std::puts(R"(
    U     U   N     N    OOOOO
    U     U   NN    N   O     O
    U     U   N N   N   O     O
    U     U   N  N  N   O     O
    U     U   N   N N   O     O
    U     U   N    NN   O     O
     UUUUU    N     N    OOOOO
    )");
    std::puts("==================================");
}

void ConsoleView::askNumPlayer() const{
    std::puts("How many players are going to play?(2-10)");
}

std::optional<std::string> ConsoleView::readTextInput(std::optional<size_t> max_input_size){
    if(_kbhit()){
        constexpr char BACKSPACE_VALUE = 8;
        char c = _getch();

        if(input_.size() && c == BACKSPACE_VALUE)
            DeleteCharacter(input_);
        else
            AddCharacter(input_, c, max_input_size);
    }
    if(input_.size() && IsEnterKey(input_.back())){
        std::optional<std::string> input = input_;
        input_.clear();

        return input;
    }

    return std::nullopt;
}

void ConsoleView::printUnoError(UnoError err) const{
    switch(err){
        case UnoError::TooFewPlayers: std::puts("Not enough players"); break;
        case UnoError::TooManyPlayers: std::puts("Max players amount exceeded"); break;
        default: assert("Unidentified UNO error code"); break;
    }
}

std::optional<int> ConsoleView::readIntegerInput(std::optional<size_t> max_input_size){
    std::optional<int> num_input = std::nullopt;
    std::optional<std::string> str = readTextInput(max_input_size);

    if(str.has_value()){
        size_t pos = 0;
        try{
            num_input = std::stoi(str.value(), &pos);
            if(pos + 1 < str.value().size())    throw std::invalid_argument("Invalid numeric characters");
            return num_input;
        }
        catch(std::invalid_argument const& ex){
            printf("%s\n",ex.what());
        }
    }

    return std::nullopt;
}