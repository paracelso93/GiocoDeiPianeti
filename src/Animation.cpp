#include "Animation.h"


void Animation::setup(std::string filePath, int frames, int rows, int cols, int height, int width) {
    this->totalFrames = frames;
    this->currentFrame = 0;
    this->rows = rows;
    this->cols = cols;
    this->size.x = width;
    this->size.y = height;
    this->texture.loadFromFile(filePath);
    sf::IntRect rec(0, 0, size.x / cols, size.y / rows);
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(rec);
}

void Animation::setPosition(sf::Vector2f position) {
    this->sprite.setPosition(position);
    this->position = position;
}

void Animation::setScale(sf::Vector2f scale) {
    this->sprite.setScale(scale);
}

void Animation::update() {
    sf::IntRect rec((this->currentFrame - floor(static_cast<float>(this->currentFrame) / static_cast<float>(this->cols)) * this->cols) * (this->size.x / this->cols),
     (floor(static_cast<float>(this->currentFrame) / static_cast<float>(this->cols))) * (this->size.y / this->rows), this->size.x / this->cols, (this->size.y / this->rows));
    this->sprite.setTextureRect(rec);
    if(this->currentFrame == this->totalFrames - 1) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
        //std::cout << currentFrame << std::endl;
    }
}

void Animation::render(sf::RenderWindow *window) {
    window->draw(this->sprite);
}