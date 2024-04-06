#include "tetris.h"

TetrisGame::TetrisGame(int newFieldHeight, int newFieldWidth, int newSizeMultiplier)
    :
    fieldHeight(newFieldHeight + 2),
	fieldWidth(newFieldWidth + 2),
    sizeMultiplier(newSizeMultiplier)
{
    gameField.resize(fieldHeight, std::vector<int>(fieldWidth, 0));
    nextFigureField.resize(2, std::vector<int>(4, 0));
    graphicEngine = new GraphicEngine(fieldHeight, fieldWidth, sizeMultiplier, "Tetris");
    currentFigure = nullptr;
    nextFigure = getRandFigure();
}

TetrisGame::~TetrisGame()
{
    graphicEngine->closeWindow();
    delete graphicEngine;
    delete currentFigure;
}

int TetrisGame::getRandFigure() {
    return (rand() * clock()) % 7;
}

void TetrisGame::startGame() {
    spawnFigure(nextFigure, {(fieldWidth - 2) / 2, 1});
    makeFence();
    while(graphicEngine->windowIsOpen()) {
        graphicEngine->pollEvent();
        drawFigure();
        drawNextFigure();
        graphicEngine->drawFrame(gameField, nextFigureField, score);
        cleanFigure();
        cleanNextFigure();
        movement();
        if (gameOver) break;
        tickHandler();
    }
}

void TetrisGame::makeFence() {
    for (size_t i = 1; i != gameField.size(); i++) {
        for (size_t j = 0; j != gameField[i].size(); j++) {
            if((j == 0 || j + 1 == gameField[i].size()) || (i + 1 == gameField.size())) {
                gameField[i][j] = 1;
            }
        }   
    }
}

void TetrisGame::printField() {
    printf("----------------------------------------------------------------------\n");
    for (size_t i = 0; i != gameField.size(); i++) {
        for (size_t j = 0; j != gameField[i].size(); j++) {
            printf("[%d]", gameField[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------\n");
}

void TetrisGame::spawnFigure(int figureType, pos_t startPos) {
    if(currentFigure) {
        drawFigure();
        findFullRows();
    }
    delete currentFigure;
    currentFigure = new Figure(figureType, startPos, &gameField);
    nextFigure = getRandFigure();
}

void TetrisGame::drawFigure() {
    coordinates_t figure = currentFigure->getFigureCoord();
    for (size_t i = 0; i != figure.size(); i++) {
        if (gameField[figure[i].y][figure[i].x] == 1) {
            gameOver = true;
            return;
        }
        gameField[figure[i].y][figure[i].x] = 1;
    }
}

void TetrisGame::drawNextFigure() {
    coordinates_t figure = currentFigure->getNextFigureCoord(nextFigure);
    for (size_t i = 0; i != figure.size(); i++) {
        nextFigureField[figure[i].y][figure[i].x] = 1;
    }
}

void TetrisGame::cleanNextFigure() {
    coordinates_t figure = currentFigure->getNextFigureCoord(nextFigure);
    for (size_t i = 0; i != figure.size(); i++) {
        nextFigureField[figure[i].y][figure[i].x] = 0;
    }
}

void TetrisGame::cleanFigure() {
        coordinates_t figure = currentFigure->getFigureCoord();

    for (size_t i = 0; i != figure.size(); i++) {
        gameField[figure[i].y][figure[i].x] = 0;
    }
}

std::map<size_t, int> TetrisGame::getRowsSums() {
    std::map<size_t, int> map;
    for (size_t i = 1; i + 1 != gameField.size(); ++i) {
        int sum = 0;
		for (size_t j = 1; j + 1 != gameField[i].size(); ++j)
            sum += gameField[i][j];
        map.insert({i, sum});
	}
    return map;
}

void TetrisGame::findFullRows() {
    int fullRowscount = 0;
    bool needToSeal = false;
    std::vector<int> combos;
    std::map<size_t, int> sumMap = getRowsSums();
    for (size_t i = 1; i + 1 != gameField.size(); ++i) {
        if (sumMap[i] == fieldWidth - 2) {
            needToSeal = true;
            fullRowscount++;
            for (size_t j = 1; j + 1 != gameField[i].size(); ++j)
                gameField[i][j] = 0;
            sumMap[i] = 0; 
        }
        else {
            if (fullRowscount > 0) {
                combos.push_back(fullRowscount);
            }
            fullRowscount = 0;
        }
	}
    combos.push_back(fullRowscount);
    for (int combo : combos) {
        switch (combo)
        {
        case 0:
            break;
        case 1:
            score += point;
            break;
        case 2:
            score += point * 4;
            break;
        case 3:
            score += point * 6;
            break;
        default:
            score += point * 8;
            break;
        }
    }
    if(needToSeal) sealField(sumMap);
}

void TetrisGame::sealField(std::map<size_t, int> sumMap) {
    size_t i = 1;
    while(i + 2 != gameField.size()) {
        if (sumMap[i] > 0) {
            if (sumMap[i + 1] == 0) {
                std::vector<int> temp = gameField[i + 1];
                int tempsum = sumMap[i + 1];
                gameField[i + 1] = gameField[i];
                sumMap[i + 1] = sumMap[i];
                gameField[i] = temp;
                sumMap[i] = tempsum;
                if (sumMap[i - 1] > 0) {
                    i--;
                    continue;
                }
            }
        }
        i++;
    }
}

void TetrisGame::movement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            gameOver = true;
            return;
        }

    if (moveTimeTick == 0) {
        startTimer = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            currentFigure->moveFigure(LEFT);
            startTimer = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            currentFigure->instantDownFigure();
            startTimer = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            currentFigure->moveFigure(RIGHT);
            startTimer = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            currentFigure->turnFigure();
            startTimer = true;
        }
    }

    if (timeTick == 20) {
        if (!currentFigure->downFigure())
            spawnFigure(nextFigure, {(fieldWidth - 2) / 2, 1});
    }
}

void TetrisGame::tickHandler() {
    timeTick+=1;
    timeTick%=21;
    if (startTimer) {
        moveTimeTick+=1;
        moveTimeTick%=11;
    }
}