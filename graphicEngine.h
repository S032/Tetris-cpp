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
    const float divider = 1.5;
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text textScore;
    sf::Text textHighScore;
public:
    GraphicEngine(int FieldHeight, int FieldWidth, int newSizeMultiplier, std::string winName);
    ~GraphicEngine();
    void pollEvent();
    void drawFrame(field_t field, field_t nextFigure, int score, int highScore);
    void drawNextFigure(field_t nextFigure);
    bool windowIsOpen();
    void closeWindow();
private:
    void set_text();
    void drawText(int score, int highscore);
    void drawField(field_t field);
};

#endif