#include "BattleMap.h"

void BattleMap::setup(int width, int height) {
    this->mWidth = width;
    this->mHeight = height;
    this->nodes = new GridNode[width * height];
    mNWidth = constants::SCREENX / width;
    mNHeight = constants::SCREENY / height;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            //std::cout << i * height + j << " ";
            nodes[i * width + j].setup(j * mNWidth, i * mNHeight, mNWidth, mNHeight);
        }
        //std::cout << std::endl;
    }
}

void BattleMap::render(sf::RenderWindow& window) {
    for(int i = 0; i < mHeight; i++) {
        for(int j = 0; j < mWidth; j++) {
            nodes[i * mWidth + j].render(window);
        }
    }
}