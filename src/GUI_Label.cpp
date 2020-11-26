#include "GUI_Label.h"  

GUI_Label::GUI_Label()
{

}

GUI_Label::~GUI_Label()
{

}

void GUI_Label::setup(std::string textStr, sf::Color color, sf::Font font, int size, sf::Vector2f position) {
    this->textStr = textStr;
    this->color = color;
    this->font = font;
    this->size = size;
    this->position = position;
    this->text.setFont(this->font);
    this->text.setCharacterSize(this->size);
    this->text.setPosition(this->position);
    this->text.setFillColor(this->color);
    this->text.setString(this->textStr);
}
void GUI_Label::render(sf::RenderWindow *window) {
    window->draw(text);
}