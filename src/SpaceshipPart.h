#ifndef SPACESHIPPART_H
#define SPACESHIPPART_H

#include <iostream>
#include <SFML/Graphics.hpp>

enum class SpaceshipPartType {
    Damage, Shield, Hull, Housing, Engine, Fuel
};

class SpaceshipPart {
    public:   
        void setup(SpaceshipPartType type, std::string filePath, int cost, int weight, std::string name);
        std::string getName() { return this->name; }
        SpaceshipPartType getType() { return this->type; }
        void setDamage(int dmg) { this->dmg = dmg; }
        void setHousing(int housing) { this->housingCapacity = housing; }
        void setFuel(int fuel) { this->fuelCapacity = fuel; }
        void setShield(int shield) { this->shieldDefense = shield; }
        void setHull(int hull) { this->hullIntegrity = hull; }
        void setEngineSpeed(int speed) { this->engineSpeed = speed; }
        int getCost() { return this->cost; }
    private:  
        SpaceshipPartType type;
        sf::Texture tex;
        sf::Sprite spr;
        std::string name;
        int cost;
        int weight;
        int dmg;
        int housingCapacity;
        int fuelCapacity;
        int shieldDefense;
        int hullIntegrity;
        float engineSpeed;
};


#endif