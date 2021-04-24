#ifndef EMPIRE_H
#define EMPIRE_H

#include <vector>

#include "Spaceship.h"
#include "DysonSphere.h"


class Empire {

    protected:
        sf::Color mEmpireColor;
        unsigned int mID;
        int mSize;
        int mFunds;
        bool mIsAI;
        std::string mRaceSprite;
        std::string mFlagSprite;
        std::string mLeaderName;
        sf::Font mFont;
        std::string mName;
        sf::RectangleShape mEmpireSquares[constants::GRIDSIDENUMBER * constants::GRIDSIDENUMBER];
        
    public:  
        Empire() {}
        ~Empire() {}
        std::vector<Planet* > mPlanets;
        std::vector<Star *> mStars;
        std::vector<Spaceship *> mSpaceships;
        std::vector<Spaceship *> mAvailableShips;
        std::vector<DysonSphere *> mDysonSpheres;
        std::vector<Building *> mAvailableBuildings;
        //std::vector<Research *> availableResearches;

        void conquerPlanet(Planet *p, Star *s, sf::Vector2i pos);
        void loosePlanet(Planet *p, Star *s) { 
            auto i = std::find(mPlanets.begin(), mPlanets.end(), p);
            mPlanets.erase(i);
            auto j = std::find(mStars.begin(), mStars.end(), s);
            mStars.erase(j);
        }
        void setLeaderName(std::string name) { this->mLeaderName = name; }
        std::string getLeaderName() { return this->mLeaderName; }
        void setName(std::string name) { this->mName = name; }
        std::string getName() { return this->mName; }
        void setRace(std::string filePath) { this->mRaceSprite = filePath; }
        void setFlag(std::string filePath) { this->mFlagSprite = filePath; }
        std::string getRace() { return this->mRaceSprite; }
        std::string getFlag() { return this->mFlagSprite; }
        void buildShip(Spaceship *s) {
            mSpaceships.push_back(s);
        }
        void looseShip(Spaceship *s) {
            auto i = std::find(mSpaceships.begin(), mSpaceships.end(), s);
            mSpaceships.erase(i);
        }

        void createDysonSphere(DysonSphere *d) {
            mDysonSpheres.push_back(d);
        }
        void looseDysonSphere(DysonSphere *d) {
            auto i = std::find(mDysonSpheres.begin(), mDysonSpheres.end(), d);
            mDysonSpheres.erase(i);
        }
        unsigned int getID() { return mID; }

        int getFunds() { return mFunds; }
        virtual void setFunds(int f) { this->mFunds = f; }
        void setAI(bool a) { this->mIsAI = a; }
        bool getAI() { return this->mIsAI; }

        sf::Color getEmpireColor() { return mEmpireColor; }
        void setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name);
        virtual void render(sf::RenderWindow& window);
};

#endif