#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <iostream>

#define LEFT 0
#define RIGHT 1
#define I 0
#define J 1
#define L 2
#define O 3
#define Z 4
#define T 5
#define S 6


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
        {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
        {{0, -1}, {0, 0}, {0, 1}, {0, 2}}
    },
    // J figure
    {
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}},
    },
}; //zzzzz

class Figure {
private:
    figure_t coords;
    pos_t pos;
    int turnPos = 0;
public:
    Figure(int figureType, pos_t startPos);
    coordinates_t getFigureCoord();
    void downFigure();
    void turnFigure();
};

#endif