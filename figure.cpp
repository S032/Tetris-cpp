#include "figure.h"
Figure::Figure(int figureType, pos_t startPos)
    :
    coords(tetrominoes[figureType]),
    pos(startPos)
{
    for (size_t i = 0; i != coords[0].size(); i++) {
        printf("x(%d);y(%d)\n", coords[0][i].x, coords[0][i].y);
    }
}

coordinates_t Figure::getFigureCoord() {
    coordinates_t projCoord;
    for (size_t j = 0; j != coords[turnPos].size(); j++) {
        pos_t projPos = {coords[turnPos][j].x + pos.x, coords[turnPos][j].y + pos.y};
        projCoord.push_back(projPos);
    }
    return projCoord;
}

void Figure::downFigure() {
    pos.y++;
}

void Figure::turnFigure() {
    turnPos += 1;
    turnPos %= coords.size();
}