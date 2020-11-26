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
    this->shape = shape;
    this->font = f;
    this->color = color;
    this->onClickColor = onClick;
    this->content = content;
    this->shape.setFillColor(color);
    this->text.setPosition({static_cast<float>(this->shape.getPosition().x + ((this->shape.getSize().x / 2.0) - (((float)strlen(content.c_str()) - 1) * (charSize)) / 2.0)), this->shape.getPosition().y + (this->shape.getSize().y - charSize) / 2});
    this->text.setCharacterSize(charSize);
    this->text.setFillColor(sf::Color::White);
    this->text.setFont(font);
    this->text.setString(content);
}

void GUI_Button::deselect() {
    this->shape.setFillColor(color);
}

bool GUI_Button::checkForClick(sf::Vector2i mousePos) {
    this->isClicked = this->shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
    return this->isClicked;
}

bool GUI_Button::isClick() {
    return this->isClicked;
}

void GUI_Button::setFunction(void (*function)()) {
    f = function;
}

void GUI_Button::click() {
    f();
    this->shape.setFillColor(this->onClickColor);
}

void GUI_Button::render(sf::RenderWindow *window) {
    window->draw(this->shape);
    window->draw(this->text);
    if(hasSprite) {
        window->draw(this->sprite);
    }
}

void GUI_Button::addImage(std::string path) {
    this->hasSprite = true;
    this->tex.loadFromFile(path);
    this->sprite.setTexture(this->tex);
    this->sprite.setPosition(this->shape.getPosition());
}
