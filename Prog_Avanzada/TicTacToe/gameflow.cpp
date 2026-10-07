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

    void ResetBuffer(char buffer[], int capacity){
        for(int slot = 0; slot < capacity; ++slot)
            buffer[slot] = '\0';
    }

    void CheckBufferCapacity(char buffer[], unsigned char& first_free_slot, int capacity){
        if(IsBufferFull(first_free_slot, capacity)){
            ResetBuffer(buffer, capacity);
            first_free_slot = 0;
        }
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
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
    if(_kbhit()){
        const unsigned char BUFFER_CAPACITY = 4;
        unsigned char first_free_slot = GetFirstBufferEmptySlot(buffer, BUFFER_CAPACITY);

        CheckBufferCapacity(buffer, first_free_slot, BUFFER_CAPACITY);
        buffer[first_free_slot] = getche();
    }
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
    char buffer[5] = {'\0'};
    int x,y;
    
    printBoard();
    while(!ttt_.isGameEnded()) {
        askPlayer(x,y,buffer);
        //system("cls");
        //if(!ttt_.play(x,y)) printBadPlay();
    }
    printBoard();
    printWinner();
}