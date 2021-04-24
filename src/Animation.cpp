#include "Animation.h"

void Animation::setup(std::string filePath, int frames, int rows, int cols, int height, int width) {
    this->mTotalFrames = frames;
    this->mCurrentFrame = 0;
    this->mRows = rows;
    this->mCols = cols;
    this->mSize.x = width;
    this->mSize.y = height;
    this->mTexture.loadFromFile(filePath);
    sf::IntRect rec(0, 0, mSize.x / cols, mSize.y / rows);
    this->mSprite.setTexture(this->mTexture);
    this->mSprite.setTextureRect(rec);
}

void Animation::setPosition(sf::Vector2f position) {
    this->mSprite.setPosition(position);
    this->mPosition = position;
}

void Animation::setScale(sf::Vector2f scale) {
    this->mSprite.setScale(scale);
}

void Animation::update() {
    sf::IntRect rec((this->mCurrentFrame - floor(static_cast<float>(this->mCurrentFrame) / static_cast<float>(this->mCols)) * this->mCols) * (this->mSize.x / this->mCols),
     (floor(static_cast<float>(this->mCurrentFrame) / static_cast<float>(this->mCols))) * (this->mSize.y / this->mRows), this->mSize.x / this->mCols, (this->mSize.y / this->mRows));
    this->mSprite.setTextureRect(rec);
    if(this->mCurrentFrame == this->mTotalFrames - 1) {
        this->mCurrentFrame = 0;
    } else {
        this->mCurrentFrame++;
        //std::cout << currentFrame << std::endl;
    }
}

void Animation::render(sf::RenderWindow& window) {
    window.draw(this->mSprite);
}
