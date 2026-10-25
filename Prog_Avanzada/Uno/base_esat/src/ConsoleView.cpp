#include "ConsoleView.hpp"

#include <cstdio>
#include <conio.h>

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

std::optional<std::string> ConsoleView::readTextInput(std::optional<size_t> max_input_size = std::nullopt){
    if(_kbhit()){
        constexpr char BACKSPACE_VALUE = 8;
        char c = _getch();

        if(c == BACKSPACE_VALUE)
            DeleteCharacter(input_);
        else
            AddCharacter(input_, c, max_input_size);
    }
    if(IsEnterKey(input_.back())) return input_;

    return std::nullopt;
}

std::optional<int> ConsoleView::readIntegerInput(std::optional<size_t> max_input_size = std::nullopt){

}