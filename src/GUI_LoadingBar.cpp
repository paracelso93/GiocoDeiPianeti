#include "GUI_LoadingBar.h"

void GUI_LoadingBar::setup(int x, int y, int w, int h, sf::Color bgcolor, sf::Color fgcolor, float max, float startvalue) {
    this->background.setPosition(x, y);
    this->foreground.setPosition(x, y);
    this->w = w;
    this->h = h;
    this->background.setSize({static_cast<float>(this->w), static_cast<float>(this->h)});
    this->foreground.setSize({static_cast<float>(this->w) * (startvalue / max), static_cast<float>(this->h)});
    this->background.setFillColor(bgcolor);
    this->foreground.setFillColor(fgcolor);
    this->max = max;
    this->currentValue = startvalue;
    this->completed = (this->max / this->currentValue == 1.f);
}

void GUI_LoadingBar::update(float dt) {
    if(!completed) {
        this->currentValue += dt;
        if(this->currentValue >= this->max) {
            this->completed = true;
        }
        this->foreground.setSize({static_cast<float>(this->w) * (this->currentValue / this->max), static_cast<float>(this->h)});
    }
}

void GUI_LoadingBar::render(sf::RenderWindow *window) {
    window->draw(this->background);
    window->draw(this->foreground);
}