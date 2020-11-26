#include "DysonSphere.h"


sf::Sprite DysonSphere::sprite = sf::Sprite();
sf::Texture DysonSphere::sphereTexture = sf::Texture();



void DysonSphere::setup(Star *star, int energy) {
    this->star = star;
    this->energyProduction = energy;
    
    this->sprite.setPosition(300 - (125.f / 2 - this->star->radius * 8), constants::STARGUIY + constants::UPPERGUIHEIGHT - (125.f / 2 - this->star->radius * 8));
    star->hasDysonSphere = true;
}

void DysonSphere::setTexture(const std::string& filePath) {
    this->sphereTexture.loadFromFile(filePath);
    this->sprite.setTexture(this->sphereTexture);


    
}

void DysonSphere::render(sf::RenderWindow *window) {
    window->draw(sprite);
}

