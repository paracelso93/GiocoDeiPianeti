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
        std::string getName() { return mName; }
        int getCost() { return mCost; }
        ResearchTypes getType() { return mType; }
        ResearchField getField() { return mField; }
        int mFinishedPercentage;
        void finishResearch(PlayerEmpire *e);
        void unlockBuilding(Building *b) { this->mBuilding = b; }
        void unlockShip(Spaceship *s) { 
            this->mSpaceship = s;
            this->mSpr.setScale({0.1f, 0.1f});
        }
        void unlockPart(SpaceshipPart *p) { this->mPart = p; }
        void setResearched(bool x) { this->mIsResearched = x; }
        bool getResearched() { return this->mIsResearched; }
        int getDifficulty() { return this->mDifficulty; }

        sf::Sprite mSpr;
    private:   
        sf::Texture mTex;
        
        std::string mName;
        ResearchTypes mType;
        ResearchField mField;
        Building *mBuilding;
        Spaceship *mSpaceship;
        SpaceshipPart *mPart;
        bool mIsResearched;
        int mDifficulty;
        int mCost;
};

#endif