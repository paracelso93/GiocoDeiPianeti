#include "Menu.h"  

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::render(sf::RenderWindow& window) {
    mCreateNew.render(window);
    mLoad.render(window);
    mQuit.render(window);
    mName.render(window);
    window.draw(mMadeSpr);
}

void Menu::setup(sf::Font font, void (*f)(), void (*f1)(), void (*f2)()) {
    this->mFont = font;
    sf::RectangleShape pShape;
    pShape.setSize({300, 120});
    pShape.setPosition({810, 500});
    mCreateNew.setup(this->mFont, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "NEW", 40);
    mCreateNew.setFunction(f);
    pShape.setPosition({810, 650});
    mLoad.setup(this->mFont, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "LOAD", 40);
    mLoad.setFunction(f1);
    pShape.setPosition({810, 800});
    mQuit.setup(this->mFont, pShape, sf::Color(255, 0, 0, 255), sf::Color(200, 0, 0, 255), "QUIT", 40);
    mQuit.setFunction(f2);
    mName.setup("GIOCO DEI PIANETI", sf::Color(150, 0, 0, 255), this->mFont, 150, {100, 200});
    mMadeTex.loadFromFile("../Assets/gui/madewithc++.png");
    mMadeSpr.setTexture(mMadeTex);
    mMadeSpr.setPosition(1780, 900);
}

void Menu::checkForClicks(sf::Vector2i mousePos) {
    if(mCreateNew.checkForClick(mousePos)) {
        mCreateNew.click();
    }
    if(mLoad.checkForClick(mousePos)) {
        mLoad.click();
    }
    if(mQuit.checkForClick(mousePos)) {
        mQuit.click();
    }
}

bool Menu::checkForHover(sf::Vector2i mousePos) {
    return (mCreateNew.checkForClick(mousePos) || mLoad.checkForClick(mousePos) || mQuit.checkForClick(mousePos));
}