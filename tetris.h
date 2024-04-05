#ifndef TETRIS_H
#define TETRIS_H

#include "graphicEngine.h"
#include "figure.h"
#include <thread>

class TetrisGame {
private:
    int fieldHeight;
    int fieldWidth;
    int sizeMultiplier;
    field_t gameField;
    GraphicEngine *graphicEngine;
    Figure *currentFigure;
    int64_t figureSpeed = 500;

public:
    TetrisGame(int newFieldHeight, int newFieldWidth, int sizeMultiplier);
    ~TetrisGame();
    void startGame();
private:
    void endGame();
    void makeFence();
    void spawnFigure(int figureType, pos_t startPos);
    void drawFigure();
    void cleanFigure();
};

#endif