#include "tetris.h"

TetrisGame::TetrisGame(int newFieldHeight, int newFieldWidth, int newSizeMultiplier)
    :
    fieldHeight(newFieldHeight + 2),
	fieldWidth(newFieldWidth + 2),
    sizeMultiplier(newSizeMultiplier)
{
    gameField.resize(fieldHeight, std::vector<int>(fieldWidth, 0));
    graphicEngine = new GraphicEngine(fieldHeight, fieldWidth, sizeMultiplier, "Tetris");
}

TetrisGame::~TetrisGame()
{
    delete graphicEngine;
}

void TetrisGame::startGame() {
    spawnFigure(J, {(fieldWidth - 2) / 2, 5});
    currentFigure->turnFigure();
    while(graphicEngine->windowIsOpen()) { 
        graphicEngine->pollEvent();
        drawFigure();
        graphicEngine->drawFrame(gameField);
        std::this_thread::sleep_for(std::chrono::milliseconds(figureSpeed));
        cleanFigure();
        currentFigure->downFigure();
    } 
}

void TetrisGame::makeFence() {
    //for (size_t i = 1; i != gameField)
}

void TetrisGame::spawnFigure(int figureType, pos_t startPos) {
    delete currentFigure;
    currentFigure = new Figure(figureType, startPos);
}

void TetrisGame::drawFigure() {
    coordinates_t figure = currentFigure->getFigureCoord();

    for (size_t i = 0; i != figure.size(); i++) {
        gameField[figure[i].y][figure[i].x] = 1;
        printf("x(%d);y(%d)\n", figure[i].x, figure[i].y); 
    }
}

void TetrisGame::cleanFigure() {
        coordinates_t figure = currentFigure->getFigureCoord();

    for (size_t i = 0; i != figure.size(); i++) {
        gameField[figure[i].y][figure[i].x] = 0; 
    }
}