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
        std::string getName() { return this->mName; }
        SpaceshipPartType getType() { return this->mType; }
        void setDamage(int dmg) { this->mDmg = dmg; }
        void setHousing(int housing) { this->mHousingCapacity = housing; }
        void setFuel(int fuel) { this->mFuelCapacity = fuel; }
        void setShield(int shield) { this->mShieldDefense = shield; }
        void setHull(int hull) { this->mHullIntegrity = hull; }
        void setEngineSpeed(int speed) { this->mEngineSpeed = speed; }
        int getCost() { return this->mCost; }
        int getWeight() { return this->mWeight; }
        int getDmg() { return this->mDmg; }
        int getHousing() { return this->mHousingCapacity; }
        int getHull() { return this->mHullIntegrity; }
        int getFuel() { return this->mFuelCapacity; }
        int getShields() { return this->mShieldDefense; }
        float getSpeed() { return this->mEngineSpeed; }
    private:  
        SpaceshipPartType mType;
        sf::Texture mTex;
        sf::Sprite mSpr;
        std::string mName;
        int mCost;
        int mWeight;
        int mDmg;
        int mHousingCapacity;
        int mFuelCapacity;
        int mShieldDefense;
        int mHullIntegrity;
        float mEngineSpeed;
};


#endif