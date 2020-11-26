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
        void render(sf::RenderWindow *window);
    private:  
        int totalFrames;
        int currentFrame;
        sf::Vector2f position;
        sf::Vector2i size;
        int rows;
        int cols;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif