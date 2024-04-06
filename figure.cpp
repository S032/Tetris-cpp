#include "figure.h"
Figure::Figure(int figureType, pos_t startPos, field_t *field)
    :
    gameField(field),
    coords(tetrominoes[figureType]),
    pos(startPos)
{}

coordinates_t Figure::getFigureCoord() {
    coordinates_t projCoord;
    for (size_t j = 0; j != coords[turnPos].size(); j++) {
        pos_t projPos = {coords[turnPos][j].x + pos.x, coords[turnPos][j].y + pos.y};
        projCoord.push_back(projPos);
    }
    return projCoord;
}

coordinates_t Figure::getNextFigureCoord(int nextFigure) {
    figure_t nextFig = tetrominoes[nextFigure];
    return nextFig[0];
}

bool Figure::downFigure() {
    coordinates_t projCoord = getFigureCoord();
    for (size_t i = 0; i != projCoord.size(); i++) {
        if ((*gameField)[projCoord[i].y + 1][projCoord[i].x] == 1) {
            return false;
        }
    }
    pos.y++;
    return true;
}

void Figure::instantDownFigure() {
    while(downFigure()); 
}

void Figure::moveFigure(int direction) {
    coordinates_t projCoord = getFigureCoord();
    for (size_t i = 0; i != projCoord.size(); i++) {
        if ((*gameField)[projCoord[i].y][projCoord[i].x + direction] == 1) {
            return;
        }
    }
    pos.x += direction;
    return;
}

void Figure::turnFigure() {
    int previousTurn = turnPos;
    turnPos += 1;
    turnPos %= coords.size();
    coordinates_t projCoord = getFigureCoord();
    for (size_t i = 0; i != projCoord.size(); i++) {
        if ((*gameField)[projCoord[i].y][projCoord[i].x] == 1) {
            turnPos = previousTurn;
            return;
        }
    }
}