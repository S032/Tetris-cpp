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
    nextFigureId = getRandFigure();
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
    spawnFigure(nextFigureId, {(fieldWidth - 2) / 2, 1});
    makeFence();
    highscore = wrHighestScore();
    while(graphicEngine->windowIsOpen()) {
        graphicEngine->pollEvent();
        drawFigure();
        drawNextFigure();
        graphicEngine->drawFrame(gameField, nextFigureField, score, highscore);
        cleanFigure(currentFigure->getFigureCoord(), gameField);
        cleanFigure(currentFigure->getNextFigureCoord(nextFigureId), nextFigureField);
        //cleanNextFigure();
        movement();
        if (gameOver) break;
        tickHandler();
    }
    if (score > highscore) {
        wrHighestScore(score);
    }
}

void TetrisGame::makeFence() {
    for (std::size_t i = 1; i != gameField.size(); i++) {
        for (std::size_t j = 0; j != gameField[i].size(); j++) {
            if((j == 0 || j + 1 == gameField[i].size()) || (i + 1 == gameField.size())) {
                gameField[i][j] = 1;
            }
        }   
    }
}

void TetrisGame::printField() {
    printf("----------------------------------------------------------------------\n");
    for (std::size_t i = 0; i != gameField.size(); i++) {
        for (std::size_t j = 0; j != gameField[i].size(); j++) {
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
    currentFigure = new Figure(figureType, startPos, gameField);
    nextFigureId = getRandFigure();
}

void TetrisGame::drawFigure() {
    coordinates_t figure = currentFigure->getFigureCoord();
    for (std::size_t i = 0; i != figure.size(); i++) {
        if (gameField[figure[i].y][figure[i].x] == 1) {
            gameOver = true;
            return;
        }
        gameField[figure[i].y][figure[i].x] = 1;
    }
}

void TetrisGame::drawNextFigure() {
    coordinates_t figure = currentFigure->getNextFigureCoord(nextFigureId);
    for (std::size_t i = 0; i != figure.size(); i++) {
        nextFigureField[figure[i].y][figure[i].x] = 1;
    }
}

void TetrisGame::cleanFigure(coordinates_t figure, field_t &field) {
    for (std::size_t i = 0; i != figure.size(); i++) {
        field[figure[i].y][figure[i].x] = 0;
    }
}

std::map<std::size_t, int> TetrisGame::getRowsSums() {
    std::map<std::size_t, int> map;
    for (std::size_t i = 1; i + 1 != gameField.size(); ++i) {
        int sum = 0;
		for (std::size_t j = 1; j + 1 != gameField[i].size(); ++j)
            sum += gameField[i][j];
        map.insert({i, sum});
	}
    return map;
}

void TetrisGame::findFullRows() {
    int fullRowscount = 0;
    bool needToSeal = false;
    std::vector<int> combos;
    std::map<std::size_t, int> sumMap = getRowsSums();
    for (std::size_t i = 1; i + 1 != gameField.size(); ++i) {
        if (sumMap[i] == fieldWidth - 2) {
            needToSeal = true;
            fullRowscount++;
            for (std::size_t j = 1; j + 1 != gameField[i].size(); ++j)
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
        if (combo == 0)
            continue;
        score += point * (combo * combo);
    }
    if(needToSeal) sealField(sumMap);
}

void TetrisGame::sealField(std::map<std::size_t, int> sumMap) {
    std::size_t i = 1;
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
            spawnFigure(nextFigureId, {(fieldWidth - 2) / 2, 1});
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

int TetrisGame::wrHighestScore() {
    std::ifstream scoreFile("resources/hightscore.txt");
    if (!scoreFile.is_open()) {
        printf("couldn't open hightscore.txt");
        exit(EXIT_FAILURE);
    }
    std::string line;
    std::getline(scoreFile, line);
    scoreFile.close();
    return std::stoi(line);
}

void TetrisGame::wrHighestScore(int highscore) {
    std::ofstream scoreFile("resources/hightscore.txt", std::ios::trunc);
    if (!scoreFile.is_open()) {
        printf("couldn't open hightscore.txt");
        exit(EXIT_FAILURE);
    }
    scoreFile << highscore;
    scoreFile.close();
}