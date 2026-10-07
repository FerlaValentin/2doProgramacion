#include "gameflow.hpp"

#include <cstdio>
#include <cstdlib>

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
}

void GameFlow::printBoard() const{
    for(int row = 0; row < cellsPerCol_; ++row){
        printSeparator(boardWidth_);
        printRow(ttt_, row, boardWidth_, cellsPerCol_);
    }
    printSeparator(boardWidth_);
}

void GameFlow::askPlayer(int& x, int& y) const{
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
    do{
        scanf("%d %d", &x, &y);
    }while(x < 0 || x > cellsPerCol_ || y < 0 || y > cellsPerCol_);
    system("cls");
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
    int x,y;
    
    while(!ttt_.isGameEnded()) {
        askPlayer(x,y);
        if(!ttt_.play(x,y)) {
            printBadPlay();
        }
    }
    printBoard();
    printWinner();
}