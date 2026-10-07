#include "tictactoe.hpp"

#include <cstdio>

namespace{
    bool IsBoardFull(const Ficha celdas[], const int maxCells){
        for(int cell = 0; cell < maxCells; cell++){
            if(celdas[cell] == Ficha::Vacio)    return false;
        }

        return true;
    }
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
    bool is_board_full = IsBoardFull(celdas, maxCells_);

    return Tictactoe::winCondition() != Ficha::Vacio || is_board_full;
}

Ficha Tictactoe::nextPlayer() const{
    int played_cells = 0;

    for(int cell = 0; cell < maxCells_; ++cell){
        if(celdas[cell] != Ficha::Vacio) played_cells++;
    }

    return played_cells % 2 ? Ficha::O : Ficha::X;
}

bool Tictactoe::play(int x, int y){
    const unsigned char SELECTED_CELL = y * cellsPerCol_ + x;

    if(celdas[SELECTED_CELL] != Ficha::Vacio) return false;
    celdas[SELECTED_CELL] = nextPlayer();

    return true;
}