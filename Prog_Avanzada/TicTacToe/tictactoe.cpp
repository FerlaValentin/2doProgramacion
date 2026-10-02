#include "tictactoe.hpp"

#include <cstdio>

static bool IsBoardFull(const Ficha celdas[], const int maxCells){
    for(int cell = 0; cell < maxCells; cell++){
        if(celdas[cell] == Ficha::Vacio)    return false;
    }

    return true;
}

Ficha Tictactoe::winCondition() const{
    if(celdas[0] == Ficha::X && celdas[1] == Ficha::X && celdas[2] == Ficha::X //HORIZONTAL
    || celdas[3] == Ficha::X && celdas[4] == Ficha::X && celdas[5] == Ficha::X //HORIZONTAL
    || celdas[6] == Ficha::X && celdas[7] == Ficha::X && celdas[8] == Ficha::X //HORIZONTAL
    || celdas[0] == Ficha::X && celdas[3] == Ficha::X && celdas[6] == Ficha::X //VERTICAL
    || celdas[1] == Ficha::X && celdas[4] == Ficha::X && celdas[7] == Ficha::X //VERTICAL
    || celdas[2] == Ficha::X && celdas[5] == Ficha::X && celdas[8] == Ficha::X //VERTICAL
    || celdas[0] == Ficha::X && celdas[4] == Ficha::X && celdas[8] == Ficha::X //DIAGONAL
    || celdas[2] == Ficha::X && celdas[4] == Ficha::X && celdas[6] == Ficha::X) //DIAGONAL
        return Ficha::X;
    if(celdas[0] == Ficha::O && celdas[1] == Ficha::O && celdas[2] == Ficha::O //HORIZONTAL
    || celdas[3] == Ficha::O && celdas[4] == Ficha::O && celdas[5] == Ficha::O //HORIZONTAL
    || celdas[6] == Ficha::O && celdas[7] == Ficha::O && celdas[8] == Ficha::O //HORIZONTAL
    || celdas[0] == Ficha::O && celdas[3] == Ficha::O && celdas[6] == Ficha::O //VERTICAL
    || celdas[1] == Ficha::O && celdas[4] == Ficha::O && celdas[7] == Ficha::O //VERTICAL
    || celdas[2] == Ficha::O && celdas[5] == Ficha::O && celdas[8] == Ficha::O //VERTICAL
    || celdas[0] == Ficha::O && celdas[4] == Ficha::O && celdas[8] == Ficha::O //DIAGONAL
    || celdas[2] == Ficha::O && celdas[4] == Ficha::O && celdas[6] == Ficha::O) //DIAGONAL
        return Ficha::O;
        
    return Ficha::Vacio;
}

bool Tictactoe::isGameEnded() const{
    bool is_board_full = IsBoardFull(celdas, maxCells);

    return Tictactoe::winCondition() != Ficha::Vacio || is_board_full;
}

static void printSeparator(int boardWidth){
    for(int i = 0; i < boardWidth; i++) printf("=");
    printf("\n");
}

static void printRow(const Tictactoe& ttt, int row_index){
    for(int row_char = 0; row_char < ttt.boardWidth; row_char++){
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

void printBoard(const Tictactoe& ttt) {
    for(int row = 0; row < ttt.cellsPerCol; ++row){
        printSeparator(ttt.boardWidth);
        printRow(ttt, row);
    }
    printSeparator(ttt.boardWidth);
}

Ficha Tictactoe::nextPlayer() const{
    int played_cells = 0;

    for(int cell = 0; cell < maxCells; ++cell){
        if(celdas[cell] != Ficha::Vacio) played_cells++;
    }

    return played_cells % 2 ? Ficha::O : Ficha::X;
}

void askPlayer(const Tictactoe& ttt, int& x, int& y){
    printf("Jugador %c: ", static_cast<char>(ttt.nextPlayer()));
    do{
        scanf("%d %d", &x, &y);
    }while(x < 0 || x > ttt.cellsPerCol || y < 0 || y > ttt.cellsPerCol);
}

bool Tictactoe::play(int x, int y){
    const unsigned char SELECTED_CELL = y * cellsPerCol + x;

    if(celdas[SELECTED_CELL] != Ficha::Vacio) return false;
    celdas[SELECTED_CELL] = nextPlayer();

    return true;
}

void printBadPlay(const Tictactoe& ttt, int x, int y) {
    printf("Invalid play. Try again\n");
}

void printWinner(const Tictactoe& ttt) {
    switch(ttt.winCondition()){
        case Ficha::X: printf("Player X wins!"); break;
        case Ficha::O: printf("Player O wins!"); break;
        case Ficha::Vacio: printf("Tie"); break;
    }
}