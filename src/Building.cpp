#include "Building.h"

void Building::setup(int cost, std::string name, std::string texturePath, BuildingTypes type) {
    this->cost = cost;
    this->name = name;
    this->buildingTexture.loadFromFile(texturePath);
    this->buildingSprite.setTexture(this->buildingTexture);
    this->type = type;
    this->buildSignal = false;
}


void Building::destroy() {
    this->empireID = 0;
}

void Building::render(sf::RenderWindow *window, int x, int y) {
    this->buildingSprite.setPosition(x, y);
    if(this->buildSignal) {
    //    std::cout << "building!" << std::endl;
        
    }
    window->draw(buildingSprite);
}