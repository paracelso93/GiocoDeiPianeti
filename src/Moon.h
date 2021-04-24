#ifndef MOON_H
#define MOON_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Constants.h"

class Moon
{
    private:
        int mOrder;
        double mT;
    public:
        void createMoon(int ord, double K, float previousDistance, constants::PlanetSize pSize);
        Moon();
        virtual ~Moon();
        float mDistance;
        float mAngle;
        float mAngularVelocity;
        float mMass;
        float mRadius;
        int mX, mY;
        sf::Color mColor;
};

#endif // MOON_H
