#include "GUI_Label.h"  

GUI_Label::GUI_Label()
{

}

GUI_Label::~GUI_Label()
{

}

void GUI_Label::setup(std::string textStr, sf::Color color, sf::Font font, int size, sf::Vector2f position) {
    this->mTextStr = textStr;
    this->mColor = color;
    this->mFont = font;
    this->mSize = size;
    this->mPosition = position;
    this->mText.setFont(this->mFont);
    this->mText.setCharacterSize(this->mSize);
    this->mText.setPosition(this->mPosition);
    this->mText.setFillColor(this->mColor);
    this->mText.setString(this->mTextStr);
}
void GUI_Label::render(sf::RenderWindow& window) {
    window.draw(mText);
}