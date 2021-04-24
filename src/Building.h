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
        int mCost;
        void setup(int cost, std::string name, std::string texturePath, BuildingTypes type);
        void setEmpire(unsigned int empireID) { this->mEmpireID = empireID; }
        unsigned int getEmpire() { return mEmpireID; }
        sf::Texture mBuildingTexture;
        sf::Sprite mBuildingSprite;
        std::string mName;
        BuildingTypes mType;
        void destroy();
        void render(sf::RenderWindow& window, int x, int y);
        bool mBuildSignal;

    private:
        unsigned int mEmpireID;
        

};

#endif