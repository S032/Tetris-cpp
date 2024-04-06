#include "tetris.h"

int main()
{
    TetrisGame *tetris;
    while (true) {
        delete tetris;
        tetris = new TetrisGame(20, 10, 25);         
        tetris->startGame();
    }
}
