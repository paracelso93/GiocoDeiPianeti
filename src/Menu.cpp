#include "Menu.h"  

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::render(sf::RenderWindow *window) {
    createNew.render(window);
    load.render(window);
    quit.render(window);
    name.render(window);
    window->draw(madeSpr);
}

void Menu::setup(sf::Font font, void (*f)(), void (*f1)(), void (*f2)()) {
    this->font = font;
    sf::RectangleShape pShape;
    pShape.setSize({300, 120});
    pShape.setPosition({810, 500});
    createNew.setup(this->font, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "NEW", 40);
    createNew.setFunction(f);
    pShape.setPosition({810, 650});
    load.setup(this->font, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "LOAD", 40);
    load.setFunction(f1);
    pShape.setPosition({810, 800});
    quit.setup(this->font, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "QUIT", 40);
    quit.setFunction(f2);
    name.setup("GIOCO DEI PIANETI", sf::Color(150, 0, 0, 255), this->font, 150, {100, 200});
    madeTex.loadFromFile("../Assets/gui/madewithc++.png");
    madeSpr.setTexture(madeTex);
    madeSpr.setPosition(1780, 900);
}

void Menu::checkForClicks(sf::Vector2i mousePos) {
    if(createNew.checkForClick(mousePos)) {
        createNew.click();
    }
    if(load.checkForClick(mousePos)) {
        load.click();
    }
    if(quit.checkForClick(mousePos)) {
        quit.click();
    }
}

bool Menu::checkForHover(sf::Vector2i mousePos) {
    return (createNew.checkForClick(mousePos) || load.checkForClick(mousePos) || quit.checkForClick(mousePos));
}