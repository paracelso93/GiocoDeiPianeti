#ifndef PLANET_H
#define PLANET_H

#include "Moon.h"
#include "Building.h"


class Planet
{
    private:
        double T, K;
        int order;
        unsigned int occupierID;

    public:
        Planet();
        virtual ~Planet();
        float radius;
        sf::Color color;
        float angularVelocity;
        float angle;
        float distance;
        float mass;
        int x, y;
        Moon moons[8];
        int numn;
        std::string name;
        //std::vector<Building *> buildings;
        std::vector<Building *> buildings;
        std::vector<Building *> availbleBuildings;
        constants::PlanetSize size;
        void createPlanet(int ord, double K, float previousDistance);
        unsigned int getOccupierID() { return occupierID; }
        void setOccupierID(unsigned int id) { this->occupierID = id; }
};

#endif // PLANET_H
