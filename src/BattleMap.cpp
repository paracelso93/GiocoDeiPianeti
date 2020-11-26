#include "BattleMap.h"

void BattleMap::setup(int width, int height) {
    this->width = width;
    this->height = height;
    this->nodes = new GridNode[width * height];
    nWidth = constants::SCREENX / width;
    nHeight = constants::SCREENY / height;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            //std::cout << i * height + j << " ";
            nodes[i * width + j].setup(j * nWidth, i * nHeight, nWidth, nHeight);
        }
        //std::cout << std::endl;
    }
}

void BattleMap::render(sf::RenderWindow *window) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            nodes[i * width + j].render(window);
        }
    }
}