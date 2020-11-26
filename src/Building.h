#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

enum class BuildingTypes {
    housing, military, production, energy
};

class Building {
    public:   
        Building() {}
        ~Building() {}
        int cost;
        void setup(int cost, std::string name, std::string texturePath, BuildingTypes type);
        void setEmpire(unsigned int empireID) { this->empireID = empireID; }
        unsigned int getEmpire() { return empireID; }
        sf::Texture buildingTexture;
        sf::Sprite buildingSprite;
        std::string name;
        BuildingTypes type;
        void destroy();
        void render(sf::RenderWindow *window, int x, int y);
        bool buildSignal;

    private:
        unsigned int empireID;
        

};

#endif