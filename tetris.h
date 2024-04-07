#ifndef TETRIS_H
#define TETRIS_H

#include "graphicEngine.h"
#include "figure.h"
#include <thread>
#include <map>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

class TetrisGame {
private:
    int fieldHeight;
    int fieldWidth;
    int sizeMultiplier;
    int nextFigure;
    int score = 0;
    int highscore = 0;
    const int point = 100;
    field_t gameField;
    field_t nextFigureField;
    GraphicEngine *graphicEngine;
    Figure *currentFigure;
    int64_t timeTick = 0;
    int64_t moveTimeTick = 0;
    bool startTimer = false;
    bool gameOver = false;
public:
    TetrisGame(int newFieldHeight, int newFieldWidth, int sizeMultiplier);
    ~TetrisGame();
    void startGame();
private:
    int getRandFigure();
    void makeFence();
    void printField();
    void spawnFigure(int figureType, pos_t startPos);
    void drawFigure();
    void drawNextFigure();
    void cleanNextFigure();
    void cleanFigure();
    std::map<size_t, int> getRowsSums();
    void findFullRows();
    void sealField(std::map<size_t, int> sumMap);
    void movement();
    void tickHandler();
    void wrHighestScore(int score);
    int wrHighestScore();
};

#endif