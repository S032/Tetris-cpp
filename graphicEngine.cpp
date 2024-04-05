#include "graphicEngine.h"

GraphicEngine::GraphicEngine(int FieldHeight, int FieldWidth, int newSizeMultiplier, std::string winName)
	:
	multiplier(newSizeMultiplier), // 2 is outline thickness
	winHeight(FieldHeight * (newSizeMultiplier + 2)),
	winWidth(FieldWidth * (newSizeMultiplier + 2))
{
	window = new sf::RenderWindow(sf::VideoMode(winWidth, winHeight), winName);
	window->setFramerateLimit(1.0f / DELTA_TIME);
}

void GraphicEngine::drawField(field_t field) {
	for (size_t y = 1; y + 1 != field.size(); ++y) {
		for (size_t x = 1; x + 1 != field[y].size(); ++x) {
			sf::RectangleShape square(sf::Vector2f(multiplier, multiplier));
			square.setPosition(x * (multiplier + 2), y * (multiplier + 2));
			square.setOutlineThickness(2.0f);
			square.setOutlineColor(sf::Color(123, 173, 83));
			if (field[y][x] == 0) square.setFillColor(sf::Color(183, 233, 143));
			else square.setFillColor(sf::Color(58, 72, 49));
			window->draw(square);
		}
	}
}

void GraphicEngine::pollEvent() {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void GraphicEngine::drawFrame(field_t field) {
		window->clear();
		drawField(field);
        window->display();
}

bool GraphicEngine::windowIsOpen() {
	return window->isOpen();
}
