#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define DELTA_TIME 1.1f

using field_t = std::vector<std::vector<int>>;

class GraphicEngine {
private:
    int winWidth;
    int winHeight;
    int multiplier;
    sf::RenderWindow *window;
public:
    GraphicEngine(int FieldHeight, int FieldWidth, int newSizeMultiplier, std::string winName);
    void pollEvent();
    void drawFrame(field_t field);
    bool windowIsOpen();
private:
    void drawField(field_t field);
};

#endif