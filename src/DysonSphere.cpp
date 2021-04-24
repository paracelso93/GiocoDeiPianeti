#include "DysonSphere.h"


sf::Sprite DysonSphere::mSprite = sf::Sprite();
sf::Texture DysonSphere::mSphereTexture = sf::Texture();



void DysonSphere::setup(Star *star, int energy) {
    this->mStar = star;
    this->mEnergyProduction = energy;
    
    this->mSprite.setPosition(300 - (125.f / 2 - this->mStar->mRadius * 8), constants::STARGUIY + constants::UPPERGUIHEIGHT - (125.f / 2 - this->mStar->mRadius * 8));
    star->mHasDysonSphere = true;
}

void DysonSphere::setTexture(const std::string& filePath) {
    this->mSphereTexture.loadFromFile(filePath);
    this->mSprite.setTexture(this->mSphereTexture);


    
}

void DysonSphere::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

