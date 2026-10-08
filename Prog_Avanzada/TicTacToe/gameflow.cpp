#include "gameflow.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>

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

        for(slot; slot <= capacity; ++slot)
            if(buffer[slot] != '\0') break;
        
        return slot;
    }

    bool IsBufferFull(int first_free_slot, int capacity){
        return first_free_slot == capacity;
    }

    bool IsAnEnterKey(char pressed_key){
        return pressed_key == 10 || pressed_key == 13;
    }

    bool IsANumber(char buffer_slot){
        return buffer_slot >= '0' && buffer_slot <= '9';
    }

    bool IsASpace(char buffer_slot){
        return buffer_slot == 32;
    }

    bool IsAValidCoord(char coord_slot, int cells_per_col){
        return coord_slot >= 0 && coord_slot < cells_per_col;
    }

    bool IsAValidCell(char first_coord, char second_coord, int cells_per_col){
        return IsAValidCoord(first_coord, cells_per_col) && IsAValidCoord(second_coord, cells_per_col);
    }

    bool IsInputValid(char buffer[], int cells_per_col){
        return IsASpace(buffer[1]) && IsAValidCell(buffer[0], buffer[2], cells_per_col); 
    }

    void ResetBuffer(char buffer[], int capacity){
        for(int slot = 0; slot < capacity; ++slot)
            buffer[slot] = '\0';
    }

    void printInvalidFormat(){
        printf("Invalid input. Correct format is \"[X] [Y]\"");
    }
}

void GameFlow::printBoard() const{
    for(int row = 0; row < cellsPerCol_; ++row){
        printSeparator(boardWidth_);
        printRow(ttt_, row, boardWidth_, cellsPerCol_);
    }
    printSeparator(boardWidth_);
}

void GameFlow::askPlayer(int& x, int& y, char buffer[]) const{
    if(_kbhit()){
        const unsigned char BUFFER_CAPACITY = 3;
        unsigned char first_free_slot = GetFirstBufferEmptySlot(buffer, BUFFER_CAPACITY);
        char pressed_key = _getch();

        if(IsBufferFull(first_free_slot, BUFFER_CAPACITY)){
            if(IsAnEnterKey(pressed_key)) buffer[BUFFER_CAPACITY] = pressed_key;
        }
        else{
            if(IsANumber(pressed_key) || IsASpace(pressed_key)){
                printf("%c", pressed_key);
                buffer[first_free_slot] = pressed_key;
            }
        }
    }
}

void GameFlow::refreshScreen() const{
    system("cls");
    printBoard();
    printCurrPlayer();
}

void GameFlow::printCurrPlayer() const{
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
}

void GameFlow::printBadPlay() const{
    printf("Invalid play. Try again\n");
}

void GameFlow::printWinner() const{
    switch(ttt_.winCondition()){
        case Ficha::X: printf("Player X wins!"); break;
        case Ficha::O: printf("Player O wins!"); break;
        case Ficha::Vacio: printf("Tie"); break;
    }
}

void GameFlow::run(){
    char buffer[4] = {'\0'};
    int x,y;
    
    printBoard();
    printCurrPlayer();
    while(!ttt_.isGameEnded()) {
        askPlayer(x,y,buffer);
        if(IsAnEnterKey(buffer[3])){
            refreshScreen();
            if(IsInputValid(buffer, cellsPerCol_)){
                if(!ttt_.play(x,y)) printBadPlay();
            }
            else
                printInvalidFormat();
        }
    }
    printBoard();
    printWinner();
}