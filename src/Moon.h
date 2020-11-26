#ifndef MOON_H
#define MOON_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Constants.h"

class Moon
{
    private:
        int order;
        double T;
    public:
        void createMoon(int ord, double K, float previousDistance, constants::PlanetSize pSize);
        Moon();
        virtual ~Moon();
        float distance;
        float angle;
        float angularVelocity;
        float mass;
        float radius;
        int x, y;
        sf::Color color;
};

#endif // MOON_H
