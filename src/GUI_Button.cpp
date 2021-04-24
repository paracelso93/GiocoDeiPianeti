#include "GUI_Button.h"

GUI_Button::GUI_Button()
{
    //ctor
}

GUI_Button::~GUI_Button()
{
    //dtor
}

void GUI_Button::setup(sf::Font f, sf::RectangleShape shape,  sf::Color color, sf::Color onClick, std::string content, int charSize) {
    this->mShape = shape;
    this->mFont = f;
    this->mColor = color;
    this->mOnClickColor = onClick;
    this->mContent = content;
    this->mShape.setFillColor(color);
    this->mText.setPosition({static_cast<float>(this->mShape.getPosition().x + ((this->mShape.getSize().x / 2.0) - (((float)strlen(content.c_str()) - 1) * (charSize)) / 2.0)), this->mShape.getPosition().y + (this->mShape.getSize().y - charSize) / 2});
    this->mText.setCharacterSize(charSize);
    this->mText.setFillColor(sf::Color::White);
    this->mText.setFont(mFont);
    this->mText.setString(content);
}

void GUI_Button::deselect() {
    this->mShape.setFillColor(mColor);
}

bool GUI_Button::checkForClick(sf::Vector2i mousePos) {
    this->mIsClicked = this->mShape.getGlobalBounds().contains(mousePos.x, mousePos.y);
    return this->mIsClicked;
}

bool GUI_Button::isClick() {
    return this->mIsClicked;
}

void GUI_Button::setFunction(void (*function)()) {
    mFunc = function;
}

void GUI_Button::click() {
    mFunc();
    this->mShape.setFillColor(this->mOnClickColor);
}

void GUI_Button::render(sf::RenderWindow& window) {
    window.draw(this->mShape);
    window.draw(this->mText);
    if(mHasSprite) {
        window.draw(this->mSprite);
    }
}

void GUI_Button::addImage(std::string path) {
    this->mHasSprite = true;
    this->mTex.loadFromFile(path);
    this->mSprite.setTexture(this->mTex);
    this->mSprite.setPosition(this->mShape.getPosition());
}
