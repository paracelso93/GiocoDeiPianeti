#ifndef PLANET_H
#define PLANET_H

#include "Moon.h"
#include "Building.h"


class Planet
{
    private:
        double mT, mK;
        int mOrder;
        unsigned int mOccupierID;

    public:
        Planet();
        virtual ~Planet();
        float mRadius;
        sf::Color mColor;
        float mAngularVelocity;
        float mAngle;
        float mDistance;
        float mMass;
        int mX, mY;
        Moon mMoons[8];
        int mNumn;
        std::string mName;
        //std::vector<Building *> buildings;
        std::vector<Building *> mBuildings;
        std::vector<Building *> mAvailableBuildings;
        constants::PlanetSize mSize;
        void createPlanet(int ord, double K, float previousDistance);
        unsigned int getOccupierID() { return mOccupierID; }
        void setOccupierID(unsigned int id) { this->mOccupierID = id; }
};

#endif // PLANET_H
