#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

class Animation {
    public:   
        void setup(std::string filePath, int frames, int rows, int cols, int height, int width);
        void setPosition(sf::Vector2f position);
        void setScale(sf::Vector2f scale);
        void update();
        void render(sf::RenderWindow& window);
    private:  
        int mTotalFrames;
        int mCurrentFrame;
        sf::Vector2f mPosition;
        sf::Vector2i mSize;
        int mRows;
        int mCols;
        sf::Texture mTexture;
        sf::Sprite mSprite;
};

#endif