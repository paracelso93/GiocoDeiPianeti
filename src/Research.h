#ifndef RESEARCH_H
#define RESEARCH_H

#include "Building.h"
#include "Spaceship.h"
#include "SpaceshipPart.h"
#include "PlayerEmpire.h"

enum class ResearchTypes {
    Buff, UnlockShipPart, UnlockBuilding, UnlockShip 
};


enum class ResearchField {
    Physics, Engineering, Biology, Chemistry 
};

class Research {
    public:   
        void setup(std::string name, int cost, ResearchTypes type, ResearchField field, std::string filePath, int difficulty);
        std::string getName() { return name; }
        int getCost() { return cost; }
        ResearchTypes getType() { return type; }
        ResearchField getField() { return field; }
        int finishedPercentage;
        void finishResearch(PlayerEmpire *e);
        void unlockBuilding(Building *b) { this->building = b; }
        void unlockShip(Spaceship *s) { 
            this->spaceship = s;
            this->spr.setScale({0.1f, 0.1f});
        }
        void unlockPart(SpaceshipPart *p) { this->part = p; }
        void setResearched(bool x) { this->isResearched = x; }
        bool getResearched() { return this->isResearched; }
        int getDifficulty() { return this->difficulty; }

        sf::Sprite spr;
    private:   
        sf::Texture tex;
        
        std::string name;
        ResearchTypes type;
        ResearchField field;
        Building *building;
        Spaceship *spaceship;
        SpaceshipPart *part;
        bool isResearched;
        int difficulty;
        int cost;
};

#endif