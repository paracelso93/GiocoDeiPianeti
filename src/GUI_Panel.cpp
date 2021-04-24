#include "GUI_Panel.h"

sf::Texture GUI_Panel::mExitTexture = sf::Texture();
bool GUI_Panel::mTexLoaded = false;


void GUI_Panel::setup(sf::Vector2f position, sf::Vector2f size, sf::Color bgcolor, sf::Color edgeColor, sf::Font font, void (*close)()) {
    this->mShape.setFillColor(bgcolor);
    this->mShape.setPosition(position);
    this->mShape.setSize(size);
    this->mShape.setOutlineThickness(5);
    this->mShape.setOutlineColor(edgeColor);
    if(!mTexLoaded) {
        this->mExitTexture.loadFromFile("../Assets/gui/exit.png");
        mTexLoaded = true;
    }

    this->mFont = font;

    mExitSprite.setTexture(this->mExitTexture);
    mExitSprite.setPosition(position.x + size.x - 40, position.y);

    sf::RectangleShape s;
    s.setPosition(position.x + size.x - 40, position.y);
    s.setSize({40, 40});
    s.setFillColor(sf::Color::White);
    mCloseButton.setup(this->mFont, s, sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 255), " ", 1);
    mCloseButton.setFunction(close);
}

void GUI_Panel::getExit(sf::Vector2i mousePos) {
    if(mCloseButton.checkForClick(mousePos)) {
        mCloseButton.click();
    }
}

void GUI_Panel::render(sf::RenderWindow& window) {
    window.draw(this->mShape);
    window.draw(this->mExitSprite);
}