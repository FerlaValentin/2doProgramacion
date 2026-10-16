#include "GameFlow.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <string.h>

#include <esat\draw.h>

namespace{
    void printSeparator(int boardWidth){
        for(int i = 0; i < boardWidth; i++) printf("=");
        printf("\n");
    }

    void printRow(const Tictactoe& ttt, int row_index, int boardWidth, int cellsPerCol){
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

    int GetFirstBufferEmptySlot(char buffer[], int capacity){
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

    int TranslateNumCharToInt(char number){
        return number - '0';
    }

    bool IsInputValid(char buffer[], int cells_per_col){
        constexpr char SPACE_ASCII_VALUE = 32;

        return IsANumber(buffer[0]) && buffer[1] == SPACE_ASCII_VALUE && IsANumber(buffer[2]);
    }
}

void ConsoleGameFlow::printBoard() const{
    for(int row = 0; row < cellsPerCol_; ++row){
        printSeparator(boardWidth_);
        printRow(ttt_, row, boardWidth_, cellsPerCol_);
    }
    printSeparator(boardWidth_);
}

void ConsoleGameFlow::refreshScreen() const{
    system("cls");
    printBoard();
}

void ConsoleGameFlow::printCurrPlayer() const{
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
}

void ConsoleGameFlow::AssignInputCoords(){
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    cxy_.X = csbiInfo.dwCursorPosition.X;
    cxy_.Y = csbiInfo.dwCursorPosition.Y;
}

void ConsoleGameFlow::printInvalidFormat(){
    refreshScreen();
    printCurrPlayer();
    printf("\nInvalid input. Correct format is \"[X] [Y]\"\n");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy_);
    resetBuffer();
}

void ConsoleGameFlow::askPlayer(){
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

void ConsoleGameFlow::assignCoordsFromBuffer(){
    x_ = TranslateNumCharToInt(buffer_[0]);
    y_ = TranslateNumCharToInt(buffer_[2]);
}

void ConsoleGameFlow::printBadPlay() const{
    printf("\nInvalid play. Try again\n");
}

void ConsoleGameFlow::resetBuffer(){
    for(int slot = 0; slot < buffer_capacity_; ++slot)
    buffer_[slot] = '\0';
}

void ConsoleGameFlow::printWinner() const{
    switch(ttt_.winCondition()){
        case Ficha::X: printf("Player X wins!"); break;
        case Ficha::O: printf("Player O wins!"); break;
        case Ficha::Vacio: printf("Tie"); break;
    }
}

void ConsoleGameFlow::run(){
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

namespace{
    void DrawSeparator(short screen_x, float separator_height){
        esat::DrawSetStrokeColor(143, 0, 255);
        esat::DrawLine(0.0f, separator_height, screen_x, separator_height);
    }
}

void GraphicGameFlow::printBoard() const{
    DrawSeparator(SCREEN_X_, EVENT_LOG_HEIGHT_);
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawLine(0.0f, EVENT_LOG_HEIGHT_ / 3, SCREEN_X_, EVENT_LOG_HEIGHT_ / 3);
    esat::DrawLine(0.0f, EVENT_LOG_HEIGHT_ / 3 * 2, SCREEN_X_, EVENT_LOG_HEIGHT_ / 3 * 2);
    esat::DrawLine(SCREEN_X_ / 3, 0.0f, SCREEN_X_ / 3, EVENT_LOG_HEIGHT_);
    esat::DrawLine(SCREEN_X_ / 3 * 2, 0.0f, SCREEN_X_ / 3 * 2, EVENT_LOG_HEIGHT_);
}

void GraphicGameFlow::printCurrPlayer() const{
    const float EVENT_LOG_MID = (SCREEN_Y_ + EVENT_LOG_HEIGHT_) / 2;
    char turn_text[9] = {'P','l','a','y','e','r',' ',static_cast<char>(ttt_.nextPlayer()), '\0'};

    esat::DrawSetFillColor(255,255,0);
    esat::DrawText(SCREEN_X_ / 3.0f, EVENT_LOG_MID, turn_text);
}

void GraphicGameFlow::askPlayer(){}

void GraphicGameFlow::printBadPlay() const{}

void GraphicGameFlow::printWinner() const{}

void GraphicGameFlow::run(){
    GraphicGameFlow::printBoard();
    GraphicGameFlow::printCurrPlayer();
}