#include "gameflow.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

namespace{
    void printSeparator(int boardWidth){
        for(int i = 0; i < boardWidth; i++) printf("=");
        printf("\n");
    }

    void printRow(const Tictactoe& ttt, int row_index, int boardWidth){
        for(int row_char = 0; row_char < boardWidth; row_char++){
            if(row_char % 2){
                if(row_char % 4 % 3 == 0)
                    printf("|");
                else{
                    const unsigned char col_index = row_char / 4;

                    printf("%c", static_cast<char>(ttt.getCell(col_index, row_index)));
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }

    int GetFirstBufferEmptySlot(const char buffer[], int capacity){
        int slot = 0;

        for(slot; slot < capacity; ++slot)
            if(buffer[slot] == '\0') break;
        
        return slot;
    }

    bool IsAnEnterKey(char pressed_key){
        return pressed_key == 10 || pressed_key == 13;
    }

    bool IsBufferFull(int first_free_slot, int letters_capacity){
        return first_free_slot == letters_capacity;
    }

    bool IsANumber(char buffer_slot){
        return buffer_slot >= '0' && buffer_slot <= '9';
    }

    void DeleteLastCharacterFromConsole(){
        constexpr char SPACE_ASCII_VALUE = 32, BACKSPACE_ASCII_VALUE = 8;
        printf("%c%c%c", BACKSPACE_ASCII_VALUE, SPACE_ASCII_VALUE, BACKSPACE_ASCII_VALUE);
    }

    bool IsAValidCoord(int coord_slot, int cells_per_col){
        return coord_slot >= 0 && coord_slot < cells_per_col;
    }

    int TranslateNumCharToInt(char number){
        return number - '0';
    }

    bool IsAValidCell(char first_coord, char second_coord, int cells_per_col){
        return IsAValidCoord(TranslateNumCharToInt(first_coord), cells_per_col) && IsAValidCoord(TranslateNumCharToInt(second_coord), cells_per_col);
    }

    bool IsInputValid(const char buffer[], int cells_per_col){
        constexpr char SPACE_ASCII_VALUE = 32;

        return buffer[1] == SPACE_ASCII_VALUE && IsAValidCell(buffer[0], buffer[2], cells_per_col); 
    }
}

void GameFlow::printBoard() const{
    for(int row = 0; row < cellsPerCol_; ++row){
        printSeparator(boardWidth_);
        printRow(ttt_, row, boardWidth_);
    }
    printSeparator(boardWidth_);
}

void GameFlow::refreshScreen() const{
    system("cls");
    printBoard();
}

void GameFlow::printCurrPlayer() const{
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
}

void GameFlow::AssignInputCoords(){
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    cxy_.X = csbiInfo.dwCursorPosition.X;
    cxy_.Y = csbiInfo.dwCursorPosition.Y;
}

void GameFlow::printInvalidFormat(){
    refreshScreen();
    printCurrPlayer();
    printf("\nInvalid input. Correct format is \"[X] [Y]\"\n");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy_);
    resetBuffer();
}

void GameFlow::askPlayer(){
    if(_kbhit()){
        constexpr char SPACE_ASCII_VALUE = 32, BACKSPACE_ASCII_VALUE = 8;
        unsigned char first_free_slot = GetFirstBufferEmptySlot(buffer_, buffer_capacity_);
        char pressed_key = _getch();

        if(IsAnEnterKey(pressed_key)){
            if(IsBufferFull(first_free_slot, buffer_capacity_ - 1))
                buffer_[buffer_capacity_ - 1] = pressed_key;
            else
                printInvalidFormat();
        }
        else{
            if(!IsBufferFull(first_free_slot, buffer_capacity_ - 1)){
                if(IsANumber(pressed_key) || pressed_key == SPACE_ASCII_VALUE){
                    printf("%c", pressed_key);
                    buffer_[first_free_slot] = pressed_key;
                }
            }
            if(pressed_key == BACKSPACE_ASCII_VALUE && first_free_slot){
                DeleteLastCharacterFromConsole();
                buffer_[first_free_slot - 1] = '\0';
            }
        }
    }
}

void GameFlow::assignCoordsFromBuffer(){
    x_ = TranslateNumCharToInt(buffer_[0]);
    y_ = TranslateNumCharToInt(buffer_[2]);
}

void GameFlow::printBadPlay() const{
    printf("\nInvalid play. Try again\n");
}

void GameFlow::resetBuffer(){
    for(int slot = 0; slot < buffer_capacity_; ++slot)
    buffer_[slot] = '\0';
}

void GameFlow::printWinner() const{
    switch(ttt_.winCondition()){
        case Ficha::X: printf("Player X wins!"); break;
        case Ficha::O: printf("Player O wins!"); break;
        case Ficha::Vacio: printf("Tie"); break;
    }
}

void GameFlow::run(){
    refreshScreen();
    printCurrPlayer();
    AssignInputCoords();
    while(!ttt_.isGameEnded()) {
        askPlayer();
        if(IsAnEnterKey(buffer_[buffer_capacity_ - 1])){
            if(IsInputValid(buffer_, cellsPerCol_)){
                assignCoordsFromBuffer();
                if(!ttt_.play(x_,y_)){
                    refreshScreen();
                    printCurrPlayer();
                    printBadPlay();
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy_);
                }
                else{
                    refreshScreen();
                    if(!ttt_.isGameEnded()) printCurrPlayer();
                }
                resetBuffer();
            }
            else
                printInvalidFormat();
        }
    }
    printWinner();
}