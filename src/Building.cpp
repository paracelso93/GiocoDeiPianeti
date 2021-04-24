#include "Building.h"

void Building::setup(int cost, std::string name, std::string texturePath, BuildingTypes type) {
    this->mCost = cost;
    this->mName = name;
    this->mBuildingTexture.loadFromFile(texturePath);
    this->mBuildingSprite.setTexture(this->mBuildingTexture);
    this->mType = type;
    this->mBuildSignal = false;
}


void Building::destroy() {
    this->mEmpireID = 0;
}

void Building::render(sf::RenderWindow& window, int x, int y) {
    this->mBuildingSprite.setPosition(x, y);
    if(this->mBuildSignal) {
    //    std::cout << "building!" << std::endl;
        
    }
    window.draw(mBuildingSprite);
}