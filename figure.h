#ifndef FIGURE_H
#define FIGURE_H

#include "graphicEngine.h"
#include <vector>
#include <iostream>

#define LEFT -1
#define RIGHT 1

struct pos_t {
    int x;
    int y;
};

using coordinates_t = std::vector<pos_t>;
using figure_t = std::vector<coordinates_t>;
using Figures = std::vector<figure_t>;

const Figures tetrominoes = {
    // I figure
    {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}}
    },
    // J figure
    {
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}},
    },
    // L figure
    {
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
    },
    // O ligure
    {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    },
    // Z Figure
    {
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{1, 0}, {1, 1}, {0, 1}, {0, 2}},
    },
    // T figure
    {
        {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{1, 0}, {1, 1}, {2, 1}, {1, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 1}},
    },
    // S Figure
    {
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
    },
}; //zzzzz

class Figure {
private:
    field_t *gameField;
    figure_t coords;
    pos_t pos;
    int turnPos = 0;
public:
    Figure(int figureType, pos_t startPos, field_t *field);
    coordinates_t getFigureCoord();
    coordinates_t getNextFigureCoord(int nextFigure);
    bool downFigure();
    void instantDownFigure();
    void moveFigure(int direction);
    void turnFigure();
};

#endif