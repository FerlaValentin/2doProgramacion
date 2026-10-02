#include "tictactoe.hpp"

int main(int, char**) {
    Tictactoe ttt;
    int x,y;
    
    while(!ttt.isGameEnded()) {
        printBoard(ttt);
        askPlayer(ttt,x,y);
        if(!ttt.play(x,y)) {
            printBadPlay(ttt,x,y);
        }
    }
    printWinner(ttt);

    return 0;
}