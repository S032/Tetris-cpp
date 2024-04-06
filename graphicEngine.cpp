#include "graphicEngine.h"

GraphicEngine::GraphicEngine(int FieldHeight, int FieldWidth, int newSizeMultiplier, std::string winName)
	:
	multiplier(newSizeMultiplier), // 2 is outline thickness
	winHeight(FieldHeight * (newSizeMultiplier + 2)),
	winWidth(FieldWidth * (newSizeMultiplier + 2))
{
	window = new sf::RenderWindow(sf::VideoMode(winWidth + ((multiplier) * 4), winHeight), winName);
	window->setFramerateLimit(60);
	if(!font.loadFromFile("resources/ChixaDemibold.ttf")) {
		printf("font dont loaded!\n");
		exit(EXIT_FAILURE);
	}
	set_text();
}

GraphicEngine::~GraphicEngine() {
	delete window;
}

void GraphicEngine::set_text() {
	textScore.setFont(font);
	textScore.setCharacterSize(multiplier / divider);
	textScore.setFillColor(sf::Color::White);

	textScore.setPosition(winWidth, (multiplier / divider + 2) + multiplier * 2 + 2);
}

void GraphicEngine::drawText(int score) {
	std::string text = "score: " + std::to_string(score);
	textScore.setString(text);
	window->draw(textScore);
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

void GraphicEngine::drawNextFigure(field_t field) {
	size_t spacout = winWidth;
	for (size_t y = 0; y != field.size(); ++y) {
		for (size_t x = 0; x != field[y].size(); ++x) {
			sf::RectangleShape square(sf::Vector2f(multiplier / divider, multiplier / divider));
			square.setPosition(x * (multiplier / divider + 2) + spacout
								, y * (multiplier / divider + 2) + multiplier + 2);
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
			exit(EXIT_SUCCESS);
    }
}

void GraphicEngine::drawFrame(field_t field, field_t nextFigure, int score) {
		window->clear();
		drawField(field);
		drawNextFigure(nextFigure);
		drawText(score);
        window->display();
}

bool GraphicEngine::windowIsOpen() {
	return window->isOpen();
}

void GraphicEngine::closeWindow() {
	window->close();
}
