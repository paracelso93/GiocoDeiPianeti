#include "GUI_Panel.h"

sf::Texture GUI_Panel::exitTexture = sf::Texture();
bool GUI_Panel::texLoaded = false;


void GUI_Panel::setup(sf::Vector2f position, sf::Vector2f size, sf::Color bgcolor, sf::Color edgeColor, sf::Font font, void (*close)()) {
    this->shape.setFillColor(bgcolor);
    this->shape.setPosition(position);
    this->shape.setSize(size);
    this->shape.setOutlineThickness(5);
    this->shape.setOutlineColor(edgeColor);
    if(!texLoaded) {
        this->exitTexture.loadFromFile("../Assets/gui/exit.png");
        texLoaded = true;
    }

    this->font = font;

    exitSprite.setTexture(this->exitTexture);
    exitSprite.setPosition(position.x + size.x - 40, position.y);

    sf::RectangleShape s;
    s.setPosition(position.x + size.x - 40, position.y);
    s.setSize({40, 40});
    s.setFillColor(sf::Color::White);
    closeButton.setup(this->font, s, sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 255), " ", 1);
    closeButton.setFunction(close);
}

void GUI_Panel::getExit(sf::Vector2i mousePos) {
    if(closeButton.checkForClick(mousePos)) {
        closeButton.click();
    }
}

void GUI_Panel::render(sf::RenderWindow *window) {
    window->draw(this->shape);
    window->draw(exitSprite);
}