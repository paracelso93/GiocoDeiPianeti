#include "GUI_LoadingBar.h"

void GUI_LoadingBar::setup(int x, int y, int w, int h, sf::Color bgcolor, sf::Color fgcolor, float max, float startvalue) {
    this->mBackground.setPosition(x, y);
    this->mForeground.setPosition(x, y);
    this->mWidth = w;
    this->mHeight = h;
    this->mBackground.setSize({static_cast<float>(this->mWidth), static_cast<float>(this->mHeight)});
    this->mForeground.setSize({static_cast<float>(this->mWidth) * (startvalue / max), static_cast<float>(this->mHeight)});
    this->mBackground.setFillColor(bgcolor);
    this->mForeground.setFillColor(fgcolor);
    this->mMax = max;
    this->mCurrentValue = startvalue;
    this->mCompleted = (this->mMax / this->mCurrentValue == 1.f);
}

void GUI_LoadingBar::update(float dt) {
    if(!mCompleted) {
        this->mCurrentValue += dt;
        if(this->mCurrentValue >= this->mMax) {
            this->mCompleted = true;
        }
        this->mForeground.setSize({static_cast<float>(this->mWidth) * (this->mCurrentValue / this->mMax), static_cast<float>(this->mHeight)});
    }
}

void GUI_LoadingBar::render(sf::RenderWindow& window) {
    window.draw(this->mBackground);
    window.draw(this->mForeground);
}